#include <V5/Core/Factory.h>
#include "Window.h"
#include "Core.h"
#include "Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

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
	return Core::Instance().GetWindow();
}

ICore& Factory::GetCore()
{
	return Core::Instance();
}

V5Rendering::IRenderer& Factory::GetRenderer()
{
	return V5Rendering::Renderer::Instance();
}

V5Rendering::IRenderer2D& Factory::GetRenderer2D()
{
	return V5Rendering::Renderer::Instance().GetRenderer2D();
}



