#include "RendererAPI.h"
#include "OpenGL/OpenGLRendererAPI.h"

using namespace V5Rendering;

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

std::unique_ptr<RendererAPI> RendererAPI::Create()
{
	switch (s_API)
	{
	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLRendererAPI>();
	default:
		break;
	}
	throw std::runtime_error("Graphics API unknown!");
	return nullptr;
}
