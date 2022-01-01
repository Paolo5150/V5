#include "TileRenderer2D.h"
#include "Buffer.h"
#include "Vertex.h"
#include <V5/Renderer/Shader.h>
#include <V5/Components/Components.h>
#include <V5/Renderer/Texture.h>
#include "Renderer.h"
#include <V5/Core/Logger.h>
#include <glm/gtc/type_ptr.hpp>
#include <V5/Debugging/Intrumentor.h>
#include <glm/glm.hpp>

using namespace V5Rendering;
using namespace V5Core;

struct TileQuadVertex
{
	glm::vec3 Position;
	glm::vec2 UV;
};

struct TileInstanceData
{
	float TextureIndex;
	glm::vec3 Position;
	glm::vec2 Scale;
	glm::vec4 Color;	
};

namespace
{
	constexpr uint32_t MaxQuads = 100000;
	uint32_t DrawCall = 0;

	std::shared_ptr<VertexArray> vao;

	Texture2D* AllTextures[32];
	int TextureIndex = 0;

	// Batching parameters
	std::shared_ptr<VertexBuffer> batchVBO;
	std::shared_ptr<IndexBuffer> batchIBO;
	std::vector<uint32_t> indices;
	uint32_t IndexCount = 0;

	// Instancing parameters
	TileInstanceData InstancedData[MaxQuads];
	TileInstanceData* CurrentInstanceDataPtr;;
	std::shared_ptr<VertexBuffer> instanceVBO;
	TileQuadVertex vertices[MaxQuads * 4];

	glm::vec4 bl = glm::vec4(-0.5, -0.5, 0.0, 1.0);
	glm::vec4 br = glm::vec4(0.5, -0.5, 0.0, 1.0);
	glm::vec4 tr = glm::vec4(0.5, 0.5, 0.0, 1.0);
	glm::vec4 tl = glm::vec4(-0.5, 0.5, 0.0, 1.0);
	std::unique_ptr<Texture2D> t;

}

TileRenderer2D::TileRenderer2D()
{
	t = Texture2D::Create(1, 1, 1);
	AllTextures[0] = t.get();
	TextureIndex++;

	auto layout = BufferLayout({
						BufferElement(ShaderDataType::Float3), // Position
						BufferElement(ShaderDataType::Float2),  // UV

		});

	// Need to create 4 vec4s to pass a matrix to the shader via vertex buffer
	auto instancedLayout = BufferLayout({
					BufferElement(ShaderDataType::Float, false, true),  // Texture index
					BufferElement(ShaderDataType::Float3, false, true),  // position
					BufferElement(ShaderDataType::Float2, false, true),  // scale
					BufferElement(ShaderDataType::Float4, false, true), // Color
		});

	TileQuadVertex quadVerts[4];

	quadVerts[0].Position = glm::vec3(-0.5, -0.5, 0.0);
	quadVerts[0].UV = glm::vec2(0, 0);

	quadVerts[1].Position = glm::vec3(0.5, -0.5, 0.0);
	quadVerts[1].UV = glm::vec2(1, 0);

	quadVerts[2].Position = glm::vec3(0.5, 0.5, 0.0);
	quadVerts[2].UV = glm::vec2(1, 1);

	quadVerts[3].Position = glm::vec3(-0.5, 0.5, 0.0);
	quadVerts[3].UV = glm::vec2(0, 1);

	batchVBO = VertexBuffer::Create(&quadVerts[0], sizeof(TileQuadVertex) * 4);
	instanceVBO = VertexBuffer::Create(sizeof(TileInstanceData) * MaxQuads);

	indices.resize(6);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;

	batchIBO = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));

	batchVBO->SetLayout(layout);
	instanceVBO->SetLayout(instancedLayout);

	vao = VertexArray::Create();
	vao->AddVertexBuffer(batchVBO);
	vao->AddVertexBuffer(instanceVBO);
	vao->SetIndexBuffer(batchIBO);
}

void TileRenderer2D::StartBatch()
{
	CurrentInstanceDataPtr = &InstancedData[0];

	m_submittedQuads = 0;
}

void TileRenderer2D::Begin(const glm::mat4& cameraViewProjection)
{
	DrawCall = 0;
	Renderer::Instance().m_cameraBuffer->SetData(&cameraViewProjection, sizeof(glm::mat4));
	StartBatch();
	Renderer::Instance().m_cameraBuffer->Bind();
}


void TileRenderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color, Texture2D* texture)
{
	if (texture != nullptr)
	{
		bool found = 0;
		for (float i = 0; i < TextureIndex; i++)
		{
			if (texture == AllTextures[(int)i])
			{
				found = 1;
				break;
			}
		}

		if (!found)
		{
			AllTextures[TextureIndex] = texture;
			TextureIndex++;
		}
	}

	(*CurrentInstanceDataPtr).Position = position;
	(*CurrentInstanceDataPtr).Scale = scale;
	(*CurrentInstanceDataPtr).Color = color;
	(*CurrentInstanceDataPtr).TextureIndex = texture == nullptr ? 0.0f : TextureIndex - 1.0f;
	CurrentInstanceDataPtr++;
	

	m_submittedQuads++;
	if (m_submittedQuads >= MaxQuads || TextureIndex >= 32)
	{
		FlushBuffer();
	}
}

void TileRenderer2D::End()
{
	FlushBuffer();
	//V5CLOG_INFO("Draw calls {0}", DrawCall);
	DrawCall = 0;
}

void TileRenderer2D::FlushBuffer()
{
	if (m_submittedQuads == 0) return;

	ShaderLibrary::GetShader("TileTextureInstanced").Bind();

	for (int i = 0; i < TextureIndex; i++)
	{
		AllTextures[i]->Bind(i);
	}

	instanceVBO->SetData(&InstancedData[0], sizeof(TileInstanceData) * m_submittedQuads);

	V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexedInstanced(*vao, m_submittedQuads);
	CurrentInstanceDataPtr = InstancedData;

	DrawCall++;
	m_submittedQuads = 0;
	TextureIndex = 1; //Reset to 1 (not 0, slot 0 is alwayys white texture)

}

void TileRenderer2D::Shutdown()
{

}

