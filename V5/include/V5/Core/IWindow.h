#pragma once
#include "../Dll.h"
#include <string>
#include <functional>

namespace V5Core
{
	class Event;

	class V5_API IWindow
	{
	public:
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual std::string GetTitle() = 0;
		virtual void SetTitle(std::string title) = 0;

		virtual void Update() = 0;
		virtual void Refresh() = 0;
		virtual void RegisterEventListener(std::function<void(Event&)> listener) = 0;
		virtual void MaximizeWindow() = 0;
		virtual bool IsQuitRequested() = 0;
	};
}