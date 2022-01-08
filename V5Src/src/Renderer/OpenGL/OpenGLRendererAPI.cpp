#include "OpenGLRendererAPI.h"
#include <V5/Debugging/Intrumentor.h>

#include <V5/Core/Logger.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Buffer.h>

using namespace V5Core;
using namespace V5Rendering;

void OpenGLRendererAPI::Init()
{
	V5LOG_INFO("Initializing OpenGL");
	if (!gladLoaderLoadGL())
	{
		V5CLOG_CRITICAL("Failed to initialize GLAD");
		throw std::runtime_error("ailed to initialize GLAD");
	}

	const GLubyte* gpu = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
	V5LOG_INFO("\t GPU: {0}", gpu);
	V5LOG_INFO("\t OpenGL: {0}", version);
	V5LOG_INFO("\t GLSL: {0}", glsl);


	glClearColor(0, 0, 0, 1);
	glViewport(0, 0, Factory::GetWindow().GetWidth(), Factory::GetWindow().GetHeight());
	glDepthFunc(GL_LESS);


}

void OpenGLRendererAPI::Shutdown()
{
	V5LOG_INFO("Shutting down OpenGL");
}

void OpenGLRendererAPI::SetDepthTestEnabled(bool enabled)
{
	if (enabled)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetCullEnabled(bool enabled)
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

void OpenGLRendererAPI::OnEvent(V5Core::Event& e)
{
	if (e.GetType() == EventType::WindowResize)
	{
		WindowResizeEvent& ev = dynamic_cast<WindowResizeEvent&>(e);
		glViewport(0, 0, ev.GetWidth(), ev.GetHeight());

	}
	else if (e.GetType() == EventType::WindowFocus)
	{
		
	}
}

void OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a) const
{
	glClearColor(r,g,b,a);
}

void OpenGLRendererAPI::SetViewport(int x, int y, int width, int height) const
{
	glViewport(x,y,width, height);
}

void OpenGLRendererAPI::RenderIndexed(VertexArray& vao)
{
	V5_PROFILE_FUNCTION();
	vao.Bind();
	vao.GetIndexBuffer().Bind();
	glDrawElements(GL_TRIANGLES, vao.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::RenderIndexed(VertexArray& vao, uint32_t indexCount)
{
	V5_PROFILE_FUNCTION();
	vao.Bind();
	vao.GetIndexBuffer().Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount)
{
	V5_PROFILE_FUNCTION();
	vao.Bind();
	vao.GetIndexBuffer().Bind();
	glDrawElementsInstanced(GL_TRIANGLES, vao.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr, instanceCount);
}


void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




