#pragma once
#include "..\Dll.h"


namespace V5Core
{
	class Window;

	class V5_API IWindowListener
	{
	public:
		virtual void OnWindowOpen(Window& window) = 0;
		virtual void OnWindowCloseRequested(Window& window) = 0;
		virtual void OnWindowResized(Window& window, int w, int h) = 0;
		virtual void OnFocusChanged(Window& window, int focused) = 0;
	};
}
