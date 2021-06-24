#include "Window.h"
#include "CoreLogger.h"
#include <V5/Core/Input.h>
#include <Event/IEventListener.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Event/InputEvents.h>

using namespace V5Core;

std::unique_ptr<Window> Window::s_Instance;

Window& Window::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<Window>();
	}

	return *s_Instance;
}

void Window::OnCloseRequest(GLFWwindow* win)
{
	WindowCloseEvent e;
	if (Window::Instance().m_eventListener)
	{
		Window::Instance().m_eventListener(e);
	}
	
}

bool Window::IsQuitRequested()
{ 
	if (m_glfwWindow == nullptr) return false;

	auto v =  glfwWindowShouldClose(m_glfwWindow); 
	if (v)
	{
		OnCloseRequest(m_glfwWindow);
	}
	return v;
}

Window::Window()
{
}

void Window::Update() 
{ 
	glfwPollEvents(); 
};

void Window::RegisterEventListener(std::function<void(Event&)> listener)
{
	if (m_eventListener == nullptr)
	{
		m_eventListener = listener;
	}
}

void Window::OnResize(GLFWwindow* win, int newWidth, int newHeight)
{
	Window::Instance().m_width = newWidth;
	Window::Instance().m_height = newHeight;

	WindowResizeEvent e(newWidth, newHeight);
	if (Window::Instance().m_eventListener)
	{
		Window::Instance().m_eventListener(e);
	}


}

void Window::OnFocusChanged(GLFWwindow* win, int focused)
{

	WindowFocusEvent e(focused);
	if (Window::Instance().m_eventListener)
	{
		Window::Instance().m_eventListener(e);
	}
}

void Window::SetTitle(std::string title)
{
	glfwSetWindowTitle(m_glfwWindow, title.c_str());
}

void Window::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Update input
	Input::KeyCallback(window, key, scancode, action, mods);

	//The KeyHold event is triggered with the OS delay (delay when you hold a key before is considered held)

	//Also, send event
	if (Input::IsKeyDown(key))
	{
		KeyPressedEvent e((KeyCode)key);
		if (Window::Instance().m_eventListener)
		{
			Window::Instance().m_eventListener(e);
		}
	}
	else if (Input::IsKeyHold(key))
	{
		KeyHoldEvent e((KeyCode)key);
		if (Window::Instance().m_eventListener)
		{
			Window::Instance().m_eventListener(e);
		}
	}

}

void Window::MaximizeWindow()
{
	glfwMaximizeWindow(m_glfwWindow);
}

void Window::OnMousePosition(GLFWwindow* window, double xpos, double ypos)
{
	Input::UpdateMousePos(xpos, ypos);
}

void  Window::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	Input::MouseCallback(button, action);

	if (Input::IsMouseButtonDown(button))
	{
		MouseBtnClickEvent e(button);
		if (Window::Instance().m_eventListener)
		{
			Window::Instance().m_eventListener(e);
		}
	}
	else if (Input::IsMouseButtonDown(button))
	{
		MouseBtnHoldEvent e(button);
		if (Window::Instance().m_eventListener)
		{
			Window::Instance().m_eventListener(e);
		}
	}

}


void Window::OpenWindow(int width, int height, std::string title)
{
	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	m_width = width;
	m_height = height;
	m_title = title;

	if (!m_glfwWindow)
	{
		V5CORE_LOG_ERROR("Error while opening the window, throwing except");
		throw std::runtime_error("Wrror while opening the window");
	}

	glfwMakeContextCurrent(m_glfwWindow);	

	//Register callbacks
	glfwSetWindowCloseCallback(m_glfwWindow, Window::OnCloseRequest);
	glfwSetWindowSizeCallback(m_glfwWindow, Window::OnResize);
	glfwSetWindowFocusCallback(m_glfwWindow, Window::OnFocusChanged);
	glfwSetKeyCallback(m_glfwWindow, Window::OnKey);
	glfwSetCursorPosCallback(m_glfwWindow, Window::OnMousePosition);
	glfwSetMouseButtonCallback(m_glfwWindow, Window::OnMouseButton);

	glfwFocusWindow(m_glfwWindow);


}