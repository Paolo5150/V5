#include "Window.h"
#include "CoreLogger.h"

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
	for (auto& l : Window::Instance().m_WindowListeners)
	{
		l->OnWindowCloseRequested(Window::Instance());
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

void Window::RegisterWindowListener(IWindowListener& listener)
{
	m_WindowListeners.push_back(&listener);
}

void Window::OnResize(GLFWwindow* win, int newWidth, int newHeight)
{
	Window::Instance().m_width = newWidth;
	Window::Instance().m_height = newHeight;

	for (auto& l : Window::Instance().m_WindowListeners)
	{
		l->OnWindowResized(Window::Instance(), newWidth, newHeight);
	}
}

void Window::OnFocusChanged(GLFWwindow* win, int focused)
{
	for (auto& l : Window::Instance().m_WindowListeners)
	{
		l->OnFocusChanged(Window::Instance(), focused);
	}
}



void Window::OpenWindow(int width, int height, std::string title)
{
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

	glfwFocusWindow(m_glfwWindow);

	for (auto& l : m_WindowListeners)
	{
		l->OnWindowOpen(*this);
	}
}