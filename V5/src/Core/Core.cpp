#include "Core.h"
#include "Core/Logger.h"
#include "CoreLogger.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include <Application/Application.h>


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
	m_Application = std::unique_ptr <Application>(app);

	//Initialize systems

	Logger::Init();

	if (!glfwInit())
	{
		V5CORE_LOG_ERROR("GLFW failed to initialize, throwing exception");
		throw std::runtime_error("GLFW failed to initialize");
	}
	V5CORE_LOG_INFO("GLFW successfully initialized");

	Window::Instance().RegisterWindowListener(*this);

	V5Core::Window::Instance().OpenWindow(winWidth, winHeight, wintitle);


	Run();
}


void Core::Run()
{
	m_isEngineRunning = true;
	m_Application->OnStart();

	while (m_isEngineRunning)
	{
		m_Application->Update();

		Window::Instance().Update();
		Sleep(1000);
	}

	V5CORE_LOG_INFO("Engine Run has ended");

	m_Application->OnQuit();
	Shutdown();
}


void Core::Shutdown()
{
	glfwTerminate();
	V5CORE_LOG_INFO("Engine successfully shutdown");
}



void Core::OnWindowOpen(Window& win)
{


}

void Core::OnWindowCloseRequested(Window& window)
{
	m_isEngineRunning = false;
	
}

void Core::OnWindowResized(Window& window, int w, int h)
{
	//V5CORE_LOG_INFO("Window resized to {0} {1}", w, h);
}

void  Core::OnFocusChanged(Window& window, int f)
{
	V5CORE_LOG_INFO("Focused: {0} ", f);

}




