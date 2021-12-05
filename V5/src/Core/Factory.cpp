#include <V5/Core/Factory.h>
#include "Window.h"
#include "Core.h"
#include "Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

using namespace V5Core;

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



