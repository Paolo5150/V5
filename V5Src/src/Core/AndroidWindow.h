#pragma once

#include <string>
#include <vector>
#include <V5/Core/IWindow.h>

namespace V5Core
{
	class Event;

	class AndroidWindow : public IWindow
	{
	public:
		friend class Core;

		AndroidWindow(int width, int height, const std::string& title) {}
		~AndroidWindow() {}

		void Update() override {}

		void RegisterEventListener(std::function<void(Event&)> listener) override {} ///< Intended for a single, main listener
		void Refresh() override {}
		int GetWidth() override { return 0; }
		int GetHeight() override { return 0; }
		void SetTitle(std::string title) override {}
		std::string GetTitle() override { return ""; }
		void MaximizeWindow() override {}
		void Destroy() override {}
		virtual void* GetNative() override { return nullptr; }

	};
}
