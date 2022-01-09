#include "VulkanRendererAPI.h"
#include <V5/Debugging/Intrumentor.h>

#include <V5/Core/Logger.h>

#include <V5/Event/WindowEvents.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Buffer.h>



using namespace V5Core;
using namespace V5Rendering;

void VulkanRendererAPI::Init()
{
	m_vulkanContext.Initialize();

}

void VulkanRendererAPI::Shutdown()
{
	m_vulkanContext.Shutdown();

}

void VulkanRendererAPI::SetDepthTestEnabled(bool enabled)
{
	
}

void VulkanRendererAPI::SetCullEnabled(bool enabled)
{
	
}

void VulkanRendererAPI::OnEvent(V5Core::Event& e)
{
	if (e.GetType() == EventType::WindowResize)
	{
		WindowResizeEvent& ev = dynamic_cast<WindowResizeEvent&>(e);

	}
	else if (e.GetType() == EventType::WindowFocus)
	{

	}
}

void VulkanRendererAPI::SetClearColor(float r, float g, float b, float a) const
{
}

void VulkanRendererAPI::SetViewport(int x, int y, int width, int height) const
{
}

void VulkanRendererAPI::RenderIndexed(VertexArray& vao)
{
	
}

void VulkanRendererAPI::RenderIndexed(VertexArray& vao, uint32_t indexCount)
{
	
}

void VulkanRendererAPI::RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount)
{
	
}


void VulkanRendererAPI::Clear()
{
}


