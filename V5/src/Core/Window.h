#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <V5/Core/IWindow.h>
#include <functional>

namespace V5Core
{
	class Event;

	class Window : public IWindow
	{
	public:
		friend class Core;

		static Window& Instance();
		Window();
		
		void OpenWindow(int width, int height, std::string title);

		void Update() override;


		void RegisterEventListener(std::function<void(Event&)> listener) override; ///< Intended for a single, main listener
		void Refresh() override {};
		int GetWidth() override { return m_width; }
		int GetHeight() override { return m_height; }
		void SetTitle(std::string title) override;
		std::string GetTitle() override { return m_title; }
		 void MaximizeWindow() override;


	private:
		static std::unique_ptr<Window> s_Instance;
		GLFWwindow* m_glfwWindow;
		int m_width;
		int m_height;
		std::string m_title;

		std::function<void(Event&)> m_eventListener;

		bool IsQuitRequested() override;


		static void OnCloseRequest(GLFWwindow* win);
		static void OnResize(GLFWwindow* win, int newWidth, int newHeight);
		static void OnFocusChanged(GLFWwindow* win, int focused);
		static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void OnMousePosition(GLFWwindow* window, double xpos, double ypos);
		static void OnMouseButton(GLFWwindow* window, int button, int action, int mods);

	};
}
