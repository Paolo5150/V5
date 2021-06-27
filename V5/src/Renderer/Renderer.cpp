#include <Renderer/Renderer.h>
#include <glad/glad.h>
#include <vector>
#include <fstream>
#include <V5/Core/Logger.h>
#include <V5/Renderer/Shader.h>
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"
#include "Vertex.h"
#include <V5/Debugging/Intrumentor.h>
#include <Core/Time.h>

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
	V5_PROFILE_FUNCTION();
	V5Core::Time::Instance().StartTimer();

	m_renderAPI = RendererAPI::Create();
	m_renderAPI->Init();

	ShaderLibrary::Add("ColorOnly", Shader::CreateFromSPIRV("Assets\\Shaders\\colorOnly.vert.spv", "Assets\\Shaders\\colorOnly.frag.spv"));

	auto& r = ShaderLibrary::GetShader("ColorOnly");
	r.Bind();

	std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f, -0.5f}, {1,0,0}},
		{{0.5f, -0.5f, -0.5f}, {0,1,0}},
		{{0.5f, 0.5f, -0.5f }, {1,1,1} },
		{{-0.5f, 0.5f, -0.5f }, {0,0,1} },
	};

	std::vector<uint32_t> indices = { 0,1,2, 2, 3, 0 };

	auto vbo = VertexBuffer::Create(vertices.data(), static_cast<uint32_t>(sizeof(Vertex) * vertices.size()));
	auto layout = Vertex::GetLayout();
	auto ibo = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));

	vbo->SetLayout(layout);

	vao = VertexArray::Create();
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ibo);

	auto time = V5Core::Time().Instance().StopTimer();
	V5CLOG_INFO("Render init time: {0}", time);
}

void Renderer::Render()
{
	//Do rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vao->Bind();
	vao->GetIndexBuffer()->Bind();
	glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

}


void Renderer::Shutdown()
{
	m_renderAPI->Shutdown();
}

void Renderer::OnEvent(V5Core::Event& e)
{
	m_renderAPI->OnEvent(e);
}


