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
	GLuint vertexbuffer;


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
		ShaderLibrary::Add("TileTextureInstanced", Shader::CreateFromSource("Shaders/tileTextureOnlyInstanced.vert", "Shaders/tileTextureOnlyInstanced.frag"));
		ShaderLibrary::Add("Simple", Shader::CreateFromSource("Shaders/simple.vert", "Shaders/simple.frag"));


		//int pos = ShaderLibrary::GetShader("TileTextureInstanced").GetAttribLocation("aPosition");
		//int uv = ShaderLibrary::GetShader("TileTextureInstanced").GetAttribLocation("aUV");
		//int textureIndex = ShaderLibrary::GetShader("TileTextureInstanced").GetAttribLocation("textureIndex");
		//int pos2 = ShaderLibrary::GetShader("TileTextureInstanced").GetAttribLocation("position");
		//int sca = ShaderLibrary::GetShader("TileTextureInstanced").GetAttribLocation("scale");
		//int col = ShaderLibrary::GetShader("TileTextureInstanced").GetAttribLocation("iColor");
		//int ubo = ShaderLibrary::GetShader("TileTextureInstanced").GetUBOLocation("ViewProj");

		//V5LOG_INFO("Pos {0}", pos);
		//V5LOG_INFO("uv {0}", uv);
		//V5LOG_INFO("textureIndex {0}", textureIndex);
		//V5LOG_INFO("pos2 {0}", pos2);
		//V5LOG_INFO("sca {0}", sca);
		//V5LOG_INFO("col {0}", col);
		//V5LOG_INFO("UBO {0}", ubo);

	}
	

	//Debug
	

}



void Renderer::DrawSample()
{





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


