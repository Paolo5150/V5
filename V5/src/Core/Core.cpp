#include "Core.h"
#include <V5/Core/PlatformDetection.h>
#include <V5/Core/Logger.h>
#include "CoreLogger.h"
#include <GLFW/glfw3.h>
#include <V5/Application/Application.h>
#include <functional>
#include <V5/Core/Input.h>
#include "Window.h"
#include "Time.h"
#include <V5/Event/Event.h>

using namespace V5Core;

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
	m_Application = app;

	//Initialize systems

	Logger::Init();
	Time::Instance().Init();

	Time::Instance().RegisterUpdateCallback(std::bind(&Core::Update, this, std::placeholders::_1));
	Time::Instance().RegisterRenderCallback(std::bind(&Core::Render, this));

	if (!glfwInit())
	{
		V5CORE_LOG_ERROR("GLFW failed to initialize, throwing exception");
		throw std::runtime_error("GLFW failed to initialize");
	}
	V5CORE_LOG_INFO("GLFW successfully initialized");

	Window::Instance().RegisterEventListener(std::bind(&Core::OnEvent, this, std::placeholders::_1));
	//This will call OnWindowOpen
	V5Core::Window::Instance().OpenWindow(winWidth, winHeight, wintitle);


	Run();
}


void Core::Run()
{
	m_isEngineRunning = true;
	m_Application->OnStart();

	Time::Instance().Reset();
	while (m_isEngineRunning)
	{
		//Update timer, will trigger calls to Update and Render
		Time::Instance().Update();

	}

	V5CORE_LOG_INFO("Engine Run has ended");

	m_Application->OnQuit();
	Shutdown();
}

void Core::Update(double dt)
{
	Window::Instance().Update(); //Poll events before application update
	m_Application->Update();
	Input::ResetDownKeys();

}

void Core::OnEvent(Event& e)
{
	if (e.GetType() == EventType::WindowClose)
	{
		m_isEngineRunning = false;
	}

	m_Application->OnEvent(e);
}


void Core::Render()
{
	Window::Instance().Refresh();
}


void Core::Shutdown()
{
	Window::Instance().m_eventListener = nullptr;
	glfwTerminate();
	V5CORE_LOG_INFO("Engine successfully shutdown");
}






