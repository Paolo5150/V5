#pragma once
#include <V5/Core/PlatformDetection.h>

#ifdef V5_PLATFORM_ANDROID
#define VK_USE_PLATFORM_ANDROID_KHR 1
#endif
#include <../Vulkan/Include/vulkan/vulkan.h>
#include <vector>
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
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;

		VkQueue m_queueGraphics;
		VkQueue m_queuePresent;

		uint32_t m_queueFamilyIndexGraphics = -1;
		uint32_t m_queueFamilyIndexPresent = -1;

		//Surface details
		VkSurfaceCapabilitiesKHR m_surfaceCapabilities;;
		VkPresentModeKHR m_surfacePresentMode;
		VkSurfaceFormatKHR m_surfaceFormat;
		VkExtent2D m_surfaceSize;

		VkSwapchainKHR m_swapChain;

		std::vector<VkImage> m_swapChainImages;
		std::vector<VkImageView> m_swapChainImageViews;

		void CreateInstance();
		void PickDevice();
		void CreateLogicalDevice();
		void CreateSurface();
		void GetSurfaceDetails();

		void CreateSwapChain();

	};
}