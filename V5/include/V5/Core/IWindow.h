#pragma once
#include <string>
#include <functional>

namespace V5Core
{
	class Event;

	class IWindow
	{

	public:
		friend class Core;

		virtual ~IWindow() = default;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual std::string GetTitle() = 0;
		virtual void SetTitle(std::string title) = 0;

		// Accessed by core only
	private:
		virtual void Update() = 0;
		virtual void Refresh() = 0;
		virtual void RegisterEventListener(std::function<void(Event&)> listener) = 0;
		virtual void MaximizeWindow() = 0;
		virtual void Destroy() = 0;
	};
}