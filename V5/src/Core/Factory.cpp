#include <Core/Factory.h>
#include "Window.h"
#include "Core.h"
using namespace V5Core;

std::unique_ptr<Factory> Factory::s_Instance;

Factory& Factory::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<Factory>();
	}

	return *s_Instance;
}

IWindow& Factory::GetWindow()
{
	return Window::Instance();
}


ICore& Factory::GetCore()
{
	return Core::Instance();

}


