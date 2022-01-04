#include <V5/Core/PlatformDetection.h>
#include "RendererAPI.h"

#ifdef V5_PLATFORM_WINDOWS
#include "OpenGL/OpenGLRendererAPI.h"
#endif
#include "OpenGLES_3/OpenGLES_3RendererAPI.h"

using namespace V5Rendering;

// Change graphics API here
#ifdef V5_PLATFORM_WINDOWS
RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
#elif defined V5_PLATFORM_ANDROID
RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGLES;
#endif

std::unique_ptr<RendererAPI> RendererAPI::Create()
{
	switch (s_API)
	{
#ifdef V5_PLATFORM_WINDOWS
	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLRendererAPI>();
	case RendererAPI::API::Vulkan:
		throw std::runtime_error("Vulkan API not implemented!");
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_unique<OpenGLES_3RendererAPI>();
#endif
	default:
		throw std::runtime_error("Graphics API unknown!");
		break;
	}
	throw std::runtime_error("Graphics API unknown!");
	return nullptr;
}
