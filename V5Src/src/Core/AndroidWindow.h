#pragma once

#include <string>
#include <vector>
#include <V5/Core/IWindow.h>
#include <glad/egl.h>
#include <V5/PlatformSpecific/AndroidWindowCallbacks.h>


namespace V5Core
{
	class Event;

	class AndroidWindow : public IWindow
	{
	public:
		friend class Core;

		AndroidWindow(int width, int height, const std::string& title, void* windowCallback);
		~AndroidWindow();

		void Update() override;

		void Refresh() override;
		int GetWidth() override { return m_width; }
		int GetHeight() override { return m_height; }
		void SetTitle(std::string title) override {}
		std::string GetTitle() override { return ""; }
		void MaximizeWindow() override;
		void Destroy() override;
		void* GetNative() override { return m_nativeWindow; }

	private:
		AndroidWindowCallbacks* m_androidWindowCallback = nullptr;
		int m_width;
		int m_height;
		void* m_nativeWindow;
	};
}
