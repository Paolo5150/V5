#include "VertexArray.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

using namespace V5Rendering;

std::unique_ptr<VertexArray> VertexArray::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLVertexArray>();
		break;
	default:
		break;
	}
}
