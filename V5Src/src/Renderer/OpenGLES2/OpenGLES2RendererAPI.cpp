#include "OpenGLES2RendererAPI.h"
#include <V5/Core/PlatformDetection.h>
#include <V5/Core/Logger.h>
#include <glad/gles2.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Buffer.h>

using namespace V5Core;
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

	glViewport(0, 0, Factory::GetWindow().GetWidth(), Factory::GetWindow().GetHeight());
	glDepthFunc(GL_LESS);


}
void OpenGLES2RendererAPI::Shutdown()
{

	gladLoaderUnloadGLES2();
	V5LOG_INFO("Unloaded OpenGLES2");

}

void OpenGLES2RendererAPI::SetDepthTestEnabled(bool enabled)
{
	if(enabled)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void OpenGLES2RendererAPI::SetCullEnabled(bool enabled)
{
	if (enabled)
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
	}
	else
	{
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
	}
}

void OpenGLES2RendererAPI::OnEvent(V5Core::Event& e)
{

}


void OpenGLES2RendererAPI::SetViewport(int x, int y, int width, int height) const
{
	glViewport(x, y, width, height);
}

void OpenGLES2RendererAPI::RenderIndexed(VertexArray& vao)
{
	vao.Bind();
	vao.GetIndexBuffer().Bind();
	glDrawElements(GL_TRIANGLES, vao.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLES2RendererAPI::RenderIndexed(VertexArray& vao, uint32_t indexCount)
{
	vao.Bind();

	vao.GetIndexBuffer().Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
void OpenGLES2RendererAPI::RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount)
{
	vao.Bind();
	vao.GetIndexBuffer().Bind();
	glDrawElementsInstanced(GL_TRIANGLES, vao.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr, instanceCount);
}

void OpenGLES2RendererAPI::SetClearColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

void OpenGLES2RendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

