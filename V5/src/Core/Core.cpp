#include "Core.h"


#include <V5/Core/PlatformDetection.h>
#include <V5/Core/Logger.h>
#include "CoreLogger.h"
#include <V5/Application/Application.h>
#include <functional>
#include <V5/Core/Input.h>
#include <V5/Core/IWindow.h>
#include "Window.h"
#include "Time.h"
#include <V5/Event/Event.h>
#include <Renderer/Renderer.h>
#include <V5/Debugging/Intrumentor.h>

using namespace V5Core;

namespace
{
	int FPS = 60;
	double frameTime = 1.0 / FPS;
}

std::unique_ptr<Core> Core::s_Instance;

Core& Core::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<Core>();
	}

	return *s_Instance;
}


Core::Core()
{

}


Core::~Core()
{
}


void Core::Start(Application* app, int winWidth, int winHeight, std::string wintitle)
{

	V5_PROFILE_BEGIN("Core", "CoreInit.json");
	{
		V5_PROFILE_FUNCTION();

		m_Application = app;

		Logger::Init();

		//This will call OnWindowOpen
		m_window =  V5Core::Window::Instance().OpenWindow(winWidth, winHeight, wintitle);	
		m_window->RegisterEventListener(std::bind(&Core::OnEvent, this, std::placeholders::_1));	

		//Renderer must be inintialized here, after context is set up
		V5Rendering::Renderer::Instance().Init();
		m_Application->OnStart();
	}

	V5_PROFILE_END();
	Run();
}


void Core::Run()
{

	m_isEngineRunning = true;

	V5_PROFILE_BEGIN("Core", "CoreUpdate.json");

	while (m_isEngineRunning)
	{
		double now = glfwGetTime();
		m_looseDeltaTime = now - m_prevTime;
		m_prevTime = now;

		auto delta = m_looseDeltaTime;
		m_accumulator += delta;

		if (m_accumulator > frameTime)
		{
			m_deltaTime = m_accumulator;
			//Update callback
			m_accumulator = 0;

			Update(m_deltaTime);
			//Render callback
			Render();
		}
	
	}

	V5CORE_LOG_INFO("Engine Run has ended");
	V5_PROFILE_END();

	V5_PROFILE_BEGIN("Core", "CoreShutdown.json");

	Shutdown();
	V5_PROFILE_END();

	system("pause");
}

void Core::Update(double dt)
{
	V5_PROFILE_FUNCTION();
	m_window->Update(); //Poll events before application update
	m_Application->Update(dt);
	Input::ResetDownKeys();

}

void Core::Render()
{
	V5_PROFILE_FUNCTION();

	V5Rendering::Renderer::Instance().GetRenderAPI().Clear();

	//Test
	m_Application->Render();
	//V5Rendering::Renderer::Instance().Render();

	// Do all ImGUI stuff here, for all layers
	m_Application->UpdateImGuiLayers();	

	m_window->Refresh();
}

void Core::OnEvent(Event& e)
{
	//If the windows is being close, the core will consume the event.
	// All systems will be shutting down in the Shutdown method (they won't receive the WindowClose event)
	if (e.GetType() == EventType::WindowClose)
	{
		m_isEngineRunning = false;
		V5CORE_LOG_INFO("WindowClose event received by Core, initiating shutdown");
		e.Consume();
	}

	if (!e.GetIsConsumed())
	{
		V5Rendering::Renderer::Instance().OnEvent(e);
		m_Application->OnEvent(e);
	}
}

void Core::Shutdown()
{
	V5_PROFILE_FUNCTION();
	m_window->Destroy();
	m_Application->OnQuit();

	V5Rendering::Renderer::Instance().Shutdown();
	V5CORE_LOG_INFO("Engine successfully shutdown");
}








