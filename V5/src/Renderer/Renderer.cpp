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
#include <V5/Renderer/Texture.h>

using namespace V5Rendering;

std::unique_ptr<Renderer> Renderer::s_Instance;

namespace
{
	std::shared_ptr<VertexArray> vao;
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<Texture2D> texture2;
	std::shared_ptr<UniformBuffer> ubo;

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
	V5Core::Time::StartTimer();


	m_renderAPI = RendererAPI::Create();
	m_renderAPI->Init();


	// Use for all shaders
	m_cameraBuffer = UniformBuffer::Create(0, sizeof(glm::mat4));

	m_renderer2D = std::make_unique<Renderer2D>();
	m_tileRenderer2D = std::make_unique<TileRenderer2D>();

	// Tests
	//ShaderLibrary::Add("Texture", Shader::CreateFromSPIRV("Assets\\Shaders\\bin\\textureOnly.vert.spv", "Assets\\Shaders\\bin\\textureOnly.frag.spv"));
	ShaderLibrary::Add("TextureInstanced", Shader::CreateFromSPIRV("Assets\\Shaders\\bin\\textureOnlyInstanced.vert.spv", "Assets\\Shaders\\bin\\textureOnlyInstanced.frag.spv"));
	ShaderLibrary::Add("TileTextureInstanced", Shader::CreateFromSPIRV("Assets\\Shaders\\bin\\tileTextureOnlyInstanced.vert.spv", "Assets\\Shaders\\bin\\tileTextureOnlyInstanced.frag.spv"));
	ShaderLibrary::Add("TextureBatched", Shader::CreateFromSPIRV("Assets\\Shaders\\bin\\textureOnlyBatched.vert.spv", "Assets\\Shaders\\bin\\textureOnlyBatched.frag.spv"));


	//texture = Texture2D::Create("Assets\\Textures\\wall.jpg");
	//texture2 = Texture2D::Create("Assets\\Textures\\smiley.png");

	//auto& r = ShaderLibrary::GetShader("Texture");
	//r.Bind();

	/*std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f, -0.5f}, {1,0,0}, {0,0}},
		{{0.5f, -0.5f, -0.5f}, {0,1,0}, {1,0}},
		{{0.5f, 0.5f, -0.5f }, {1,1,1} , {1,1}},
		{{-0.5f, 0.5f, -0.5f }, {0,0,1} , {0,1}},
	};

	std::vector<uint32_t> indices = { 0,1,2, 2, 3, 0 };

	auto vbo = VertexBuffer::Create(vertices.data(), static_cast<uint32_t>(sizeof(Vertex) * vertices.size()));
	auto layout = Vertex::GetLayout();
	auto ibo = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));

	vbo->SetLayout(layout);

	vao = VertexArray::Create();
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ibo);*/

	std::vector<float> color = { 1,0,0,1 };
	//Test UBO
	//ubo = UniformBuffer::Create(0, color.data(), sizeof(float) * 4);

	auto time = V5Core::Time::StopTimer();
	V5CLOG_INFO("Render init time: {0}", time);
}

void Renderer::Render()
{
	V5_PROFILE_FUNCTION();

	/*ShaderLibrary::GetShader("Texture").Bind();
	//Do rendering
	texture2->Bind(0);
	texture->Bind(1);
	ubo->Bind();

	m_renderAPI->RenderIndexed(*vao);*/

}


void Renderer::Shutdown()
{
	V5_PROFILE_FUNCTION();
	m_renderAPI->Shutdown();
}

void Renderer::OnEvent(V5Core::Event& e)
{
	m_renderAPI->OnEvent(e);
}


