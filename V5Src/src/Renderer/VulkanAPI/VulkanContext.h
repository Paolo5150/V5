#pragma once
#include <V5/Core/PlatformDetection.h>

#ifdef V5_PLAFTORM_ANDROID
#define VK_USE_PLATFORM_ANDROID_KHR 1
#endif
#include <../Vulkan/Include/vulkan/vulkan.h>

namespace V5Rendering
{
	class VulkanContext
	{
	public:
		void Initialize();
		void Shutdown();

	private:
		VkInstance m_vulkanInstance;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
		VkDevice m_device;
		VkSurfaceKHR m_surface;
		VkQueue m_queueGraphics;

		int32_t m_queueFamilyGraphics = -1;

		void CreateInstance();
		void PickDevice();
		void CreateLogicalDevice();
		void CreateSurface();

	};
}