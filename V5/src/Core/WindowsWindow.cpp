#include "WindowsWindow.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_opengl3_loader.h>
#include <ImGui/imgui_impl_glfw.h>
#include "CoreLogger.h"
#include <V5/Core/Input.h>
#include <Event/IEventListener.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Event/InputEvents.h>
#include <glad/glad.h>
#include <V5/Debugging/Intrumentor.h>

using namespace V5Core;

WindowsWindow::WindowsWindow(int width, int height, const std::string& title)
{
	if (!glfwInit())
	{
		V5CORE_LOG_ERROR("GLFW failed to initialize, throwing exception");
		throw std::runtime_error("GLFW failed to initialize");
	}
	V5CORE_LOG_INFO("GLFW successfully initialized");

	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!m_glfwWindow)
	{
		V5CORE_LOG_ERROR("Error while opening the window, throwing except");
		throw std::runtime_error("Wrror while opening the window");
	}

	glfwMakeContextCurrent(m_glfwWindow);

	m_data.Title = title;
	m_data.Width = width;
	m_data.Height = height;
	m_data.VSync = false;


	glfwSetWindowUserPointer(m_glfwWindow, &m_data);

	//Register callbacks
	glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow* win) {

		auto data = (WindowData*)glfwGetWindowUserPointer(win);
		WindowCloseEvent e;
		data->m_eventListener(e);
	
	});

	glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* win, int newWidth, int newHeight) {

		auto data = (WindowData*)glfwGetWindowUserPointer(win);
		data->Width = newWidth;
		data->Height = newHeight;

		WindowResizeEvent e(newWidth, newHeight);
		if (data->m_eventListener)
		{
			data->m_eventListener(e);
		}


	});

	glfwSetWindowFocusCallback(m_glfwWindow, [](GLFWwindow* win, int focused) {

		WindowFocusEvent e(focused);
		auto data = (WindowData*)glfwGetWindowUserPointer(win);

		if (data->m_eventListener)
		{
			data->m_eventListener(e);
		}
	
	});

	glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods) {

		auto data = (WindowData*)glfwGetWindowUserPointer(win);

		//Update input
		Input::KeyCallback(win, key, scancode, action, mods);

		//The KeyHold event is triggered with the OS delay (delay when you hold a key before is considered held)

		//Also, send event
		if (Input::IsKeyDown(key))
		{
			KeyPressedEvent e((KeyCode)key);
			if (data->m_eventListener)
			{
				data->m_eventListener(e);
			}
		}
		else if (Input::IsKeyHold(key))
		{
			KeyHoldEvent e((KeyCode)key);
			if (data->m_eventListener)
			{
				data->m_eventListener(e);
			}
		}

	});

	glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double xpos, double ypos) {
		Input::UpdateMousePos(xpos, ypos);

	});

	glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* win, int button, int action, int mods) {

		auto data = (WindowData*)glfwGetWindowUserPointer(win);

		Input::MouseCallback(button, action);

		if (Input::IsMouseButtonDown(button))
		{
			MouseBtnClickEvent e(button);
			if (data->m_eventListener)
			{
				data->m_eventListener(e);
			}
		}
		else if (Input::IsMouseButtonDown(button))
		{
			MouseBtnHoldEvent e(button);
			if (data->m_eventListener)
			{
				data->m_eventListener(e);
			}
		}
	
	});

	glfwFocusWindow(m_glfwWindow);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, false);
	ImGui_ImplOpenGL3_Init("#version 410");
}

WindowsWindow::~WindowsWindow()
{
}

void WindowsWindow::Update()
{
	glfwPollEvents();
};

void WindowsWindow::Refresh()
{
	glfwSwapBuffers(m_glfwWindow);
}

void WindowsWindow::Destroy()
{
	V5_PROFILE_FUNCTION();

	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
	V5CORE_LOG_INFO("Windows destroyed, GLFW terminated");
}

void WindowsWindow::RegisterEventListener(std::function<void(Event&)> listener)
{
	if (m_data.m_eventListener == nullptr)
	{
		m_data.m_eventListener = listener;
	}
}

void WindowsWindow::SetTitle(std::string title)
{
	glfwSetWindowTitle(m_glfwWindow, title.c_str());
}

void WindowsWindow::MaximizeWindow()
{
	glfwMaximizeWindow(m_glfwWindow);
}



