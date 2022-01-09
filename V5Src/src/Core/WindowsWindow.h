#pragma once
#ifdef V5_PLATFORM_WINDOWS
#include <GLFW/glfw3.h>
#endif
#include <string>
#include <vector>
#include <V5/Core/IWindow.h>
#include <functional>

namespace V5Core
{
	class Event;

	class WindowsWindow : public IWindow
	{
	public:
		friend class Core;

		WindowsWindow(int width, int height, const std::string& title);
		~WindowsWindow();

		void Update() override;

		void RegisterEventListener(std::function<void(Event&)> listener) override; ///< Intended for a single, main listener
		void Refresh() override;
		int GetWidth() override { return m_data.Width; }
		int GetHeight() override { return m_data.Height; }
		void SetTitle(std::string title) override;
		std::string GetTitle() override { return m_data.Title; }
		void MaximizeWindow() override;
		void Destroy() override;
		void* GetNative() override;

	private:
		GLFWwindow* m_glfwWindow;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			std::function<void(Event&)> m_eventListener;
		};

		WindowData m_data;
	};
}
