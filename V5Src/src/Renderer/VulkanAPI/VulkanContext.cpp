#include "VulkanContext.h"
#include <V5/Core/PlatformDetection.h>
#include <V5/Core/Logger.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>

#ifdef V5_PLATFORM_WINDOWS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif

using namespace V5Rendering;
using namespace V5Core;

void VulkanContext::Initialize()
{
	CreateInstance();
	PickDevice();
	CreateLogicalDevice();
	CreateSurface();

	V5CLOG_INFO("Vulkan ready!");

}
void VulkanContext::CreateInstance()
{
	V5CLOG_INFO("Initializing Vulkan");
	VkApplicationInfo app_info = {};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = NULL;
	app_info.pApplicationName = "V5";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "V5";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	uint32_t extensionsCount = 0;
	const char** extensions;

#ifdef V5_PLATFORM_WINDOWS
	extensions = glfwGetRequiredInstanceExtensions(&extensionsCount);
#elif defined V5_PLATFORM_ANDROID
	std::vector<const char*> e = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME };
	extensions = e.data();
	extensionsCount = e.size();
#endif
	VkInstanceCreateInfo inst_info = {};
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.flags = 0;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledLayerCount = 0;

	inst_info.enabledExtensionCount = extensionsCount;
	inst_info.ppEnabledExtensionNames = extensions;


	VkResult res = vkCreateInstance(&inst_info, NULL, &m_vulkanInstance);
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

//	uint32_t extensionsCount = 0;
//	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
//	std::vector<VkExtensionProperties> m_supportedInstanceExtensions;
//
//	m_supportedInstanceExtensions.resize(extensionsCount);
//	m_supportedInstanceExtensions.resize(extensionsCount);
//	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, m_supportedInstanceExtensions.data());
//
//	//Uncomment to view the list of supported extensions
//	for (const auto& extension : m_supportedInstanceExtensions)
//		V5CLOG_INFO("Extension: {0}", extension.extensionName);
//
}

void VulkanContext::Shutdown()
{
	vkDestroyDevice(m_device, nullptr);
	vkDestroyInstance(m_vulkanInstance, NULL);
	V5CLOG_INFO("Vulkan shutdown");

}

void VulkanContext::PickDevice()
{
	// Count devices
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_vulkanInstance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		V5CLOG_CRITICAL("No devices available!");
		V5LOG_CRITICAL("No devices available!");
		throw std::runtime_error("No devices available");
	}

	V5CLOG_INFO("Devices {0}", deviceCount);

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_vulkanInstance, &deviceCount, devices.data());

	//TODO: do better GPU evaluation?
	// Pick first device, unless it's discrete type
	m_physicalDevice = devices[0];
	for (size_t i = 0; i < devices.size(); i++)
	{
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(devices[i], &props);
		switch (props.deviceType)
		{

		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			m_physicalDevice = devices[i];

			break;

		}
	}

	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(m_physicalDevice, &props);
	V5CLOG_INFO("GPU: {0}", props.deviceName);
	V5CLOG_INFO("API: {0}", props.apiVersion);

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, queueFamilies.data());

	V5CLOG_INFO("Q families: {0}", queueFamilyCount);

	int i = 0;
	for (const auto& queueFamily : queueFamilies) 
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			m_queueFamilyGraphics = i;
			V5CLOG_INFO("Graphics family: {0}", m_queueFamilyGraphics);
		}

		i++;
	}

	if (m_queueFamilyGraphics == -1)
	{
		V5CLOG_ERROR("Graphics family queue not available, aborting");
		throw std::runtime_error("Graphics family queue not available, aborting");
	}

}

void VulkanContext::CreateLogicalDevice()
{
	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = m_queueFamilyGraphics;
	queueCreateInfo.queueCount = 1; // TODO: if multithreading, more queues?

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledLayerCount = 0; //TODO: change this when enablid validation layers

	if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) 
	{
		V5CLOG_ERROR("Failed to create logical device");
		throw std::runtime_error("Failed to create logical device");
	}

	vkGetDeviceQueue(m_device, m_queueFamilyGraphics, 0, &m_queueGraphics);

}

void VulkanContext::CreateSurface()
{
#ifdef V5_PLATFORM_WINDOWS

	GLFWwindow* w = (GLFWwindow*)(V5Core::Factory().GetWindow().GetNative());

	if (glfwCreateWindowSurface(m_vulkanInstance, w, nullptr, &m_surface) != VK_SUCCESS)
	{
		V5CLOG_ERROR("Failed to create surface");
		throw std::runtime_error("Failed to create surface");
	}
#endif
#ifdef V5_PLATFORM_ANDROID

	ANativeWindow* w = (ANativeWindow*)(V5Core::Factory().GetWindow().GetNative());

	VkAndroidSurfaceCreateInfoKHR createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.window = w;
	if (vkCreateAndroidSurfaceKHR(m_vulkanInstance, &createInfo, nullptr, &m_surface) != VK_SUCCESS)
	{
		V5CLOG_ERROR("Failed to create surface");
	}

	V5CLOG_INFO("Surface OK!");
#endif

}




