#include "OpenGLRendererAPI.h"
#include <V5/Core/Logger.h>
#include <Core/CoreLogger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>

using namespace V5Core;
using namespace V5Rendering;

void OpenGLRendererAPI::Init()
{
	V5CORE_LOG_INFO("Initializing OpenGL");
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		V5CLOG_CRITICAL("Failed to initialize GLAD");
		throw std::runtime_error("ailed to initialize GLAD");
	}

	const GLubyte* gpu = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
	V5CORE_LOG_INFO("\t GPU: {0}", gpu);
	V5CORE_LOG_INFO("\t OpenGL: {0}", version);
	V5CORE_LOG_INFO("\t GLSL: {0}", glsl);

	glEnable(GL_SCISSOR_TEST);

	glClearColor(0, 0, 0, 1);
	glViewport(0, 0, Factory::Instance().GetWindow().GetWidth(), Factory::Instance().GetWindow().GetHeight());

}

void OpenGLRendererAPI::Shutdown()
{
	V5CORE_LOG_INFO("Shutting down OpenGL");
}

void OpenGLRendererAPI::OnEvent(V5Core::Event& e)
{
	if (e.GetType() == EventType::WindowResize)
	{
		V5CLOG_INFO("W {0} H {0}", Factory::Instance().GetWindow().GetWidth(), Factory::Instance().GetWindow().GetHeight());
		glViewport(0, 0, Factory::Instance().GetWindow().GetWidth(), Factory::Instance().GetWindow().GetHeight());


	}
	else if (e.GetType() == EventType::WindowFocus)
	{
		
	}
}

