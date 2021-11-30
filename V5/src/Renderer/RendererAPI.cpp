#include <V5/Core/PlatformDetection.h>
#include "RendererAPI.h"

#include "OpenGL/OpenGLRendererAPI.h"
using namespace V5Rendering;

// Change graphics API here
RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

std::unique_ptr<RendererAPI> RendererAPI::Create()
{
	switch (s_API)
	{
	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLRendererAPI>();
	case RendererAPI::API::Vulkan:
		throw std::runtime_error("Vulkan API not implemented!");
	default:
		break;
	}
	throw std::runtime_error("Graphics API unknown!");
	return nullptr;
}
