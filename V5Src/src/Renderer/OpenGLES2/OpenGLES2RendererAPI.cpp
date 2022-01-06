#include "OpenGLES2RendererAPI.h"
#include <V5/Core/PlatformDetection.h>
#include <V5/Core/Logger.h>
#include <glad/gles2.h>


using namespace V5Rendering;

void OpenGLES2RendererAPI::Init()
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

	SetClearColor(1, 0, 0, 1);
}
void OpenGLES2RendererAPI::Shutdown()
{

}

void OpenGLES2RendererAPI::OnEvent(V5Core::Event& e)
{

}


void OpenGLES2RendererAPI::SetViewport(int x, int y, int width, int height) const
{}

void OpenGLES2RendererAPI::RenderIndexed(VertexArray& aroverride)
{}

void OpenGLES2RendererAPI::RenderIndexed(VertexArray& aroverride, uint32_t indexCount)
{

}
void OpenGLES2RendererAPI::RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount)
{}

void OpenGLES2RendererAPI::SetClearColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

void OpenGLES2RendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

