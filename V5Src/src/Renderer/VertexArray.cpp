#include "VertexArray.h"
#include "RendererAPI.h"
#ifdef V5_PLATFORM_WINDOWS

#include "OpenGL/OpenGLVertexArray.h"
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
		break;
	default:
		break;
	}
}
