#include "OpenGLES_3RendererAPI.h"
#include <V5/Core/PlatformDetection.h>
#include <glad/gles2.h>


using namespace V5Rendering;

void OpenGLES_3RendererAPI::Init()
{
	if (!gladLoaderLoadGLES2())
	{
		throw std::runtime_error("failed to initialize GLAD");
	}
}
void OpenGLES_3RendererAPI::Shutdown()
{

}

void OpenGLES_3RendererAPI::OnEvent(V5Core::Event& e)
{

}


void OpenGLES_3RendererAPI::SetViewport(int x, int y, int width, int height) const
{}

void OpenGLES_3RendererAPI::RenderIndexed(VertexArray& aroverride)
{}

void OpenGLES_3RendererAPI::RenderIndexed(VertexArray& aroverride, uint32_t indexCount)
{

}
void OpenGLES_3RendererAPI::RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount)
{}

void OpenGLES_3RendererAPI::SetClearColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

void OpenGLES_3RendererAPI::Clear()
{

}

