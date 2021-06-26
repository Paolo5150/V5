#include <Renderer/Renderer.h>
#include <glad/glad.h>
#include <vector>
#include <fstream>
#include <V5/Core/Logger.h>
#include <V5/Renderer/Shader.h>
#include "Renderer/OpenGL/OpenGLShader.h"
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"

using namespace V5Rendering;

std::unique_ptr<Renderer> Renderer::s_Instance;

namespace
{
	std::shared_ptr<VertexArray> vao;

}

Renderer& Renderer::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<Renderer>();
	}

	return *s_Instance;
}

void Renderer::Init()
{
	m_renderAPI = RendererAPI::Create();
	m_renderAPI->Init();

	//TODO: refactor obiously
	ShaderLibrary::Add("ColorOnly", Shader::CreateFromSPIRV("Assets\\Shaders\\colorOnly.vert.spv", "Assets\\Shaders\\colorOnly.frag.spv"));

	auto& r = ShaderLibrary::GetShader("ColorOnly");
	r.Bind();

	//TODO: Refactor, no opengl code here

	std::vector<float> vertices = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.0f, 0.5f, -0.5f
	};

	auto vbo = VertexBuffer::Create(vertices.data(), sizeof(vertices));
	auto layout = BufferLayout::BufferLayout({
		BufferElement(ShaderDataType::Float3,"Position")
		});

	vbo->SetLayout(layout);

	vao = VertexArray::Create();
	vao->AddVertexBuffer(vbo);

}

void Renderer::Render()
{
	//Do rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vao->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);


}


void Renderer::Shutdown()
{
	m_renderAPI->Shutdown();
}

void Renderer::OnEvent(V5Core::Event& e)
{
	m_renderAPI->OnEvent(e);
}


