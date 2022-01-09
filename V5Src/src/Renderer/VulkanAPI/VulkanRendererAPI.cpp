#include "VulkanRendererAPI.h"
#include <V5/Core/PlatformDetection.h>
#include <V5/Debugging/Intrumentor.h>

#include <V5/Core/Logger.h>

#include <V5/Event/WindowEvents.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Buffer.h>

#ifdef V5_PLATFORM_WINDOWS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif

using namespace V5Core;
using namespace V5Rendering;

void VulkanRendererAPI::Init()
{
	V5CLOG_INFO("Initializing Vulkan");

	VkApplicationInfo app_info = {};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = NULL;
	app_info.pApplicationName = "V5";
	app_info.applicationVersion = 1;
	app_info.pEngineName = "V5";
	app_info.engineVersion = 1;
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo inst_info = {};
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.flags = 0;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledExtensionCount = 0;
	inst_info.ppEnabledExtensionNames = NULL;
	inst_info.enabledLayerCount = 0;
	inst_info.ppEnabledLayerNames = NULL;

	VkResult res;

	res = vkCreateInstance(&inst_info, NULL, &m_vulkanInstance);
	if (res == VK_ERROR_INCOMPATIBLE_DRIVER) {
		V5CLOG_ERROR("Cannot find a compatible Vulkan ICD");
		V5LOG_ERROR("Cannot find a compatible Vulkan ICD");
		exit(-1);
	}
	else if (res) {
		V5CLOG_ERROR("Failed to initialize Vulkan intance");
		V5LOG_ERROR("Failed to initialize Vulkan intance");
		exit(-1);
	}

	V5CLOG_INFO("Vulkan instance ok");

}

void VulkanRendererAPI::Shutdown()
{
	vkDestroyInstance(m_vulkanInstance, NULL);
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




