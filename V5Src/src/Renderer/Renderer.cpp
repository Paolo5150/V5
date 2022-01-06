#include <Renderer/Renderer.h>
#include <glad/gl.h>
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
	//V5_PROFILE_FUNCTION();
	m_renderAPI = RendererAPI::Create();
	m_renderAPI->Init();

	// Use for all shaders
	m_cameraBuffer = UniformBuffer::Create(0, sizeof(glm::mat4));
	m_renderer2D = std::make_unique<Renderer2D>();
	m_tileRenderer2D = std::make_unique<TileRenderer2D>();

	if (m_renderAPI->GetAPI() == RendererAPI::API::OpenGL)
	{
		// Tests
		ShaderLibrary::Add("TextureInstanced", Shader::CreateFromSPIRV("Shaders/bin/textureOnlyInstanced.vert.spv", "Shaders/bin/textureOnlyInstanced.frag.spv"));
		ShaderLibrary::Add("TileTextureInstanced", Shader::CreateFromSPIRV("Shaders/bin/tileTextureOnlyInstanced.vert.spv", "Shaders/bin/tileTextureOnlyInstanced.frag.spv"));
		ShaderLibrary::Add("TextureBatched", Shader::CreateFromSPIRV("Shaders/bin/textureOnlyBatched.vert.spv", "Shaders/bin/textureOnlyBatched.frag.spv"));

	}
	else if(m_renderAPI->GetAPI() == RendererAPI::API::OpenGLES)
	{
		ShaderLibrary::Add("TextureInstanced", Shader::CreateFromSource("Shaders/textureOnly.vert", "Shaders/textureOnly.frag"));
	}
	

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


