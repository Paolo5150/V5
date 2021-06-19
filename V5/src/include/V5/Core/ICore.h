#pragma once

#include "../Dll.h"
#include <string>

namespace V5Core
{
	class Application;

	class V5_API ICore
	{
	public:
		virtual void Start(Application* app, int winWidth, int winHeight, std::string wintitle) = 0;

	};
}
