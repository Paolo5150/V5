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



	//This will call OnWindowOpen
	m_window =  V5Core::Window::Instance().OpenWindow(winWidth, winHeight, wintitle);	
	m_window->RegisterEventListener(std::bind(&Core::OnEvent, this, std::placeholders::_1));
	

	//Renderer
	V5Rendering::Renderer::Instance().Init();
	}
	V5_PROFILE_END();
	Run();

}


void Core::Run()
{
	m_isEngineRunning = true;
	m_Application->OnStart();

	Time::Instance().Reset();
	V5_PROFILE_BEGIN("Core", "CoreUpdate.json");

	while (m_isEngineRunning)
	{
		//Update timer, will trigger calls to Update and Render
		Time::Instance().Update();

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
	m_Application->Update();
	Input::ResetDownKeys();

}

void Core::Render()
{
	V5_PROFILE_FUNCTION();

	V5Rendering::Renderer::Instance().Render();

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
	CloseLibs();
	V5CORE_LOG_INFO("Engine successfully shutdown");
}

//Just put the glfw terminate in function so i can probilfe it
void  Core::CloseLibs()
{
#ifdef V5_PLATFORM_WINDOWS
	V5_PROFILE_FUNCTION();
	glfwTerminate();
#endif

}







