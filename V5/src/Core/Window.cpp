#include "Window.h"
#include "CoreLogger.h"
#include <V5/Core/Input.h>
#include <Event/IEventListener.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Event/InputEvents.h>
#include <V5/Core/PlatformDetection.h>
#include <V5/Debugging/Intrumentor.h>
#include "WindowsWindow.h"

using namespace V5Core;

std::unique_ptr<Window> Window::s_Instance;

Window& Window::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<Window>();
	}

	return *s_Instance;
}


Window::Window()
{
}

std::unique_ptr<IWindow> Window::OpenWindow(int width, int height, std::string title)
{
	V5_PROFILE_FUNCTION();
#ifdef V5_PLATFORM_WINDOWS
	auto w = std::make_unique<WindowsWindow>(width, height, title);
	return std::move(w);
#endif


}