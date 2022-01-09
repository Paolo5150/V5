#include <V5/Core/PlatformDetection.h>
#include "RendererAPI.h"

#ifdef V5_PLATFORM_ANDROID
#include "VulkanAPI/VulkanRendererAPI.h"
#include "OpenGLES2/OpenGLES2RendererAPI.h"
#endif

#ifdef V5_PLATFORM_WINDOWS
	#include "VulkanAPI/VulkanRendererAPI.h"
	#include "OpenGL/OpenGLRendererAPI.h"
#endif



using namespace V5Rendering;

// Change graphics API here
#ifdef V5_PLATFORM_WINDOWS
	#ifdef V5_GRAPHICS_API_VULKAN
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;
	#elif defined V5_GRAPHICS_API_OPENGL
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	#endif

#elif defined V5_PLATFORM_ANDROID 
	#ifdef V5_GRAPHICS_API_VULKAN
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;
	#elif defined V5_GRAPHICS_API_OPENGL
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGLES;
	#endif
#endif



std::unique_ptr<RendererAPI> RendererAPI::Create()
{
	switch (s_API)
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLRendererAPI>();
	case RendererAPI::API::Vulkan:
		return std::make_unique<VulkanRendererAPI>();

#endif
#ifdef V5_PLATFORM_ANDROID
	case RendererAPI::API::OpenGLES:
		return std::make_unique<OpenGLES2RendererAPI>();
	case RendererAPI::API::Vulkan:
		return std::make_unique<VulkanRendererAPI>();
#endif
	default:
		throw std::runtime_error("Graphics API unknown!");
		break;
	}
	throw std::runtime_error("Graphics API unknown!");
	return nullptr;
}
