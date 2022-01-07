/*
* Copyright (C) 2010 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include <malloc.h>

#include <V5/Core/Factory.h>
#include <V5/Core/ICore.h>
#include <V5/Renderer/IRenderer.h>
#include <V5/Core/AssetManager.h>
#include <glad/gles2.h>
#include <glad/egl.h>
#include <V5/PlatformSpecific/AndroidWindowCallbacks.h>
#include "GameApp.h"
#include <iostream>
#include <sstream>
#include <fstream>
/**
* Our saved state data.
*/
struct saved_state {
	float angle;
	int32_t x;
	int32_t y;
};

/**
* Shared state for our app.
*/
struct engine {
	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

	int animating;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
	struct saved_state state;
	bool ready = false;
};


static GameApp gameApp;
static AndroidWindowCallbacks awb;
static struct engine engine;

/**
* Initialize an EGL context for the current display.
*/
static int engine_init_display(struct engine* engine) {
	// initialize OpenGL ES and EGL
	if (!gladLoaderLoadEGL(NULL)) {
		LOGW("Failed to initialize EGL");
		return -1;
	};

	/*
	* Here specify the attributes of the desired configuration.
	* Below, we select an EGLConfig with at least 8 bits per color
	* component compatible with on-screen windows
	*/
	const EGLint attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};
	EGLint w, h, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	
	eglInitialize(display, 0, 0);

	/* Here, the application chooses the configuration it desires. In this
	* sample, we have a very simplified selection process, where we pick
	* the first EGLConfig that matches our criteria */
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	* guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	* As soon as we picked a EGLConfig, we can safely reconfigure the
	* ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);

	EGLint contextAttrs[] = {
		EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE
	};

	context = eglCreateContext(display, config, NULL, contextAttrs);
	
	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		LOGW("Unable to eglMakeCurrent");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;
	engine->state.angle = 0;
	engine->ready = 1;

	return 0;
}

/**
* Process the next input event.
*/
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
	struct engine* engine = (struct engine*)app->userData;


	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {

		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);

		auto act = AKeyEvent_getAction(event);
		
		if (act == AKEY_EVENT_ACTION_DOWN)
		{
			awb.OnSingleTap(engine->state.x, engine->state.y);
		}
		

		return 1;
	}
	return 0;
}

/**
* Process the next main command.
*/
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
	struct engine* engine = (struct engine*)app->userData;
	switch (cmd) {
	case APP_CMD_SAVE_STATE:
		// The system has asked us to save our current state.  Do so.
		engine->app->savedState = malloc(sizeof(struct saved_state));
		*((struct saved_state*)engine->app->savedState) = engine->state;
		engine->app->savedStateSize = sizeof(struct saved_state);
		break;
	case APP_CMD_INIT_WINDOW:
		// The window is being shown, get it ready.
		if (engine->app->window != NULL) {
			engine_init_display(engine);

		}
		break;
	case APP_CMD_TERM_WINDOW:
		// The window is being hidden or closed, clean it up.
		awb.OnWindowClose();
		break;
	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.
		if (engine->accelerometerSensor != NULL) {
			ASensorEventQueue_enableSensor(engine->sensorEventQueue,
				engine->accelerometerSensor);
			// We'd like to get 60 events per second (in microseconds).
			ASensorEventQueue_setEventRate(engine->sensorEventQueue,
				engine->accelerometerSensor, (1000L / 60) * 1000);
		}
		break;
	case APP_CMD_LOST_FOCUS:
		// When our app loses focus, we stop monitoring the accelerometer.
		// This is to avoid consuming battery while not being used.
		if (engine->accelerometerSensor != NULL) {
			ASensorEventQueue_disableSensor(engine->sensorEventQueue,
				engine->accelerometerSensor);
		}
		// Also stop animating.
		engine->animating = 0;
		//engine_draw_frame(engine);
		break;
	}
}

static void PollEvents()
{
	int ident;
	int events;
	struct android_poll_source* source;
	while ( (ident = ALooper_pollAll(0, NULL, &events, (void**)(&source))) >= 0)
	{

		if (engine.app->destroyRequested != 0) {
			break;
		}
		// Process this event.
		if (source != NULL) {
			source->process(engine.app, source);
			continue;
		}
		break;
	}

}


static void Refresh()
{
	eglSwapBuffers(engine.display, engine.surface);
}

static void CloseDisplay()
{
	if (engine.display != EGL_NO_DISPLAY) {
		eglMakeCurrent(engine.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (engine.context != EGL_NO_CONTEXT) {
			eglDestroyContext(engine.display, engine.context);
		}
		if (engine.surface != EGL_NO_SURFACE) {
			eglDestroySurface(engine.display, engine.surface);
		}
		eglTerminate(engine.display);
	}
	engine.animating = 0;
	engine.display = EGL_NO_DISPLAY;
	engine.context = EGL_NO_CONTEXT;
	engine.surface = EGL_NO_SURFACE;
}

/**
* This is the main entry point of a native application that is using
* android_native_app_glue.  It runs in its own thread, with its own
* event loop for receiving input events and doing other things.
*/
void android_main(struct android_app* state) {

	memset(&engine, 0, sizeof(engine));
	state->userData = &engine;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.app = state;

	// Prepare to monitor accelerometer
	engine.sensorManager = ASensorManager_getInstance();
	engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
		ASENSOR_TYPE_ACCELEROMETER);
	engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
		state->looper, LOOPER_ID_USER, NULL, NULL);

	if (state->savedState != NULL) {
		// We are starting with a previous saved state; restore from it.
		engine.state = *(struct saved_state*)state->savedState;
	}
	engine.animating = 1;
	// loop waiting for stuff to do.

	awb.PollEvents = PollEvents;
	awb.Refresh = Refresh;
	awb.CloseWindow = CloseDisplay;

	// Test getting assets
	// // These files are to be placed under the assets folder in the project and are part of the APK
	//AAssetManager* amanager = state->activity->assetManager;
	//AAsset* asset = AAssetManager_open(amanager, "textureOnly.frag", AASSET_MODE_BUFFER);
	//
	//if (asset)
	//{
	//	long size = AAsset_getLength(asset);
	//	char* buffer = (char*)malloc(sizeof(char) * size);
	//	AAsset_read(asset, buffer, size);
	//	LOGI("%s", buffer);
	//	AAsset_close(asset);
	//}
	// 

	//Set the path to asset folder
	V5Core::AssetManager::Instance().Initialize(state->activity->obbPath + std::string("/Assets"));
	// Test reading using plain C++

	LOGI("Size %d", sizeof(float));
	// This while loop is done to get the event of the screen being ready.
	// That will set engine.ready to true, so we justmp out of this while loop and start the Core loop
	while (!engine.ready) {

		// Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source;

		while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
			(void**)&source)) >= 0) {

			// Process this event.
			if (source != NULL) {
				source->process(state, source);
			}				
		}

	}
	V5Core::Factory().GetCore().Start(&gameApp, engine.width, engine.height, "asd", &awb);

}
