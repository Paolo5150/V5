#pragma once
#include <GLFW/glfw3.h>
#include <string>

#include <vector>
#include <Core/IWindowListener.h>
#include <Core/IWindow.h>


namespace V5Core
{
	class Window : public IWindow
	{
	public:
		static Window& Instance();
		Window();
		
		void OpenWindow(int width, int height, std::string title);

		void Update() override { glfwPollEvents(); };
		void RegisterWindowListener(IWindowListener& listener) override;
		bool IsQuitRequested() override;
		void Refresh() override {};
		int GetWidth() override { return m_width; }
		int GetHeight() override { return m_height; }
		std::string GetTitle() override { return m_title; }

	private:
		static std::unique_ptr<Window> s_Instance;
		GLFWwindow* m_glfwWindow;
		int m_width;
		int m_height;
		std::string m_title;

		std::vector<IWindowListener*> m_WindowListeners;


		static void OnCloseRequest(GLFWwindow* win);
		static void OnResize(GLFWwindow* win, int newWidth, int newHeight);
		static void OnFocusChanged(GLFWwindow* win, int focused);
	};
}
