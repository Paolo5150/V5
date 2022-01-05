#include "OpenGLES_3RendererAPI.h"
#include <V5/Core/PlatformDetection.h>
#include <V5/Core/Logger.h>
#include <glad/gles2.h>


using namespace V5Rendering;

void OpenGLES_3RendererAPI::Init()
{
	if (!gladLoaderLoadGLES2())
	{
		throw std::runtime_error("failed to initialize GLAD");
	}

	const GLubyte* gpu = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
	V5LOG_INFO("\t GPU: {0}", gpu);
	V5LOG_INFO("\t OpenGL: {0}", version);
	V5LOG_INFO("\t GLSL: {0}", glsl);
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
	glClear(GL_COLOR_BUFFER_BIT);
}

