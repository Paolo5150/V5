#include "VertexArray.h"
#include "RendererAPI.h"
#ifdef V5_PLATFORM_WINDOWS

#include "OpenGL/OpenGLVertexArray.h"
#endif

#ifdef V5_PLATFORM_ANDROID

#include "OpenGLES2/OpenGLES2VertexArray.h"
#endif
using namespace V5Rendering;

std::unique_ptr<VertexArray> VertexArray::Create()
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS

	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLVertexArray>();
#endif
#ifdef V5_PLATFORM_ANDROID

	case RendererAPI::API::OpenGLES:
		return std::make_unique<OpenGLES2VertexArray>();
#endif
		break;
	default:
		break;
	}
}
