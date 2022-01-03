#pragma once
#include <string>
#include <vector>
#include <V5/Core/IWindow.h>
#include <functional>

namespace V5Core
{
	class Event;

	class Window
	{
	public:
		friend class Core;

		static Window& Instance();
		Window();
		
		std::unique_ptr<IWindow> OpenWindow(int width, int height, std::string title);


	private:	
		static std::unique_ptr<Window> s_Instance;


	};
}
