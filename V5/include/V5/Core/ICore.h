#pragma once

#include <string>

namespace V5Core
{
	class Application;
	class IWindow;
	class Event;

	class ICore
	{
	public:
		virtual void Start(Application* app, int winWidth, int winHeight, std::string wintitle) = 0;
		virtual IWindow& GetWindow() = 0;
		virtual void TriggerEvent(Event& event) = 0;
	};
}
