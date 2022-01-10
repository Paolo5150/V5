#include "Renderer2D.h"
#include "Buffer.h"
#include "Vertex.h"
#include <V5/Renderer/Shader.h>
#include <V5/Components/Components.h>
#include <V5/Renderer/Texture.h>
#include "Renderer.h"
#include <V5/Core/Logger.h>
#include <glm/gtc/type_ptr.hpp>
#include <V5/Debugging/Intrumentor.h>
#include <V5/Core/AssetManager.h>
#include <glm/glm.hpp>

using namespace V5Rendering;
using namespace V5Core;

struct QuadVertex
{
	glm::vec3 Position;
	glm::vec2 UV;
};

struct QuadVertexBatched
{
	glm::vec3 Position;
	glm::vec2 UV;
	glm::vec4 Color;
	float TextureIndex;
};

struct InstanceData
{
	float TextureIndex;
	glm::vec4 Color;
	glm::mat4 ModelMat;
};

namespace
{
	bool UseInstancing = 1; // If 1, instancing, if 0, batching
	constexpr uint32_t MaxQuads = 100000;
	std::shared_ptr<VertexArray> vao;
	uint32_t DrawCall = 0;

	Texture2D* AllTextures[32];
	int TextureIndex = 0;

	// Batching parameters
	uint32_t MaxVertices = MaxQuads * 4;
	uint32_t MaxIndices = MaxQuads * 6;
	std::shared_ptr<VertexBuffer> batchVBO;
	std::shared_ptr<IndexBuffer> batchIBO;
	std::vector<uint32_t> indices;
	uint32_t IndexCount = 0;
	QuadVertexBatched verticesBatched[MaxQuads * 4];
	QuadVertexBatched* CurrentVertexPtr;


	// Instancing parameters
	InstanceData InstancedData[MaxQuads];
	InstanceData* CurrentInstanceDataPtr;;
	std::shared_ptr<VertexBuffer> instanceVBO;
	QuadVertex vertices[MaxQuads * 4];

	glm::vec4 bl = glm::vec4(-0.5, -0.5, 0.0, 1.0);
	glm::vec4 br = glm::vec4(0.5, -0.5, 0.0, 1.0);
	glm::vec4 tr = glm::vec4(0.5, 0.5, 0.0, 1.0);
	glm::vec4 tl = glm::vec4(-0.5, 0.5, 0.0, 1.0);
	std::unique_ptr<Texture2D> whiteTexture;
}

Renderer2D::Renderer2D()
{
	auto td = AssetManager::Instance().CreateColorTextureData(1, 1, 1);
	whiteTexture = Texture2D::Create(td);
	AllTextures[0] = whiteTexture.get();
	TextureIndex++;

	if (!UseInstancing)
	{
		auto layout = BufferLayout({
				BufferElement(ShaderDataType::Float3), // Position
				BufferElement(ShaderDataType::Float2),  // UV
				BufferElement(ShaderDataType::Float4),  // Color
				BufferElement(ShaderDataType::Float),  // Texture index
			});


		batchVBO = VertexBuffer::Create(sizeof(QuadVertexBatched) * MaxVertices);

		indices.resize(MaxIndices);
		// All possible indices
		int counter = 0;
		for (size_t i = 0; i < MaxIndices; i += 6)
		{
			indices[i] = 0 + (counter * 4);
			indices[i + 1] = 1 + (counter * 4);
			indices[i + 2] = 2 + (counter * 4);

			indices[i + 3] = 2 + (counter * 4);
			indices[i + 4] = 3 + (counter * 4);
			indices[i + 5] = 0 + (counter * 4);
			counter++;
		}

		batchIBO = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));

		batchVBO->SetLayout(layout);

		vao = VertexArray::Create();
		vao->AddVertexBuffer(batchVBO);
		vao->SetIndexBuffer(batchIBO);
	}
	else
	{
		auto layout = BufferLayout({
						BufferElement(ShaderDataType::Float3), // Position
						BufferElement(ShaderDataType::Float2),  // UV

			});

		// Need to create 4 vec4s to pass a matrix to the shader via vertex buffer
		auto instancedLayout = BufferLayout({
						BufferElement(ShaderDataType::Float, false, true),  // Texture index
						BufferElement(ShaderDataType::Float4, false, true),  // Color
						BufferElement(ShaderDataType::Float4, false, true), // Model matrix
						BufferElement(ShaderDataType::Float4, false, true), 
						BufferElement(ShaderDataType::Float4, false, true), 
						BufferElement(ShaderDataType::Float4, false, true), 

			});

		QuadVertex quadVerts[4];
		
		quadVerts[0].Position = glm::vec3(-0.5, -0.5, 0.0);
		quadVerts[0].UV = glm::vec2(0,0);

		quadVerts[1].Position = glm::vec3(0.5, -0.5, 0.0);
		quadVerts[1].UV = glm::vec2(1, 0);

		quadVerts[2].Position = glm::vec3(0.5, 0.5, 0.0);
		quadVerts[2].UV = glm::vec2(1, 1);

		quadVerts[3].Position = glm::vec3(-0.5, 0.5, 0.0);
		quadVerts[3].UV = glm::vec2(0, 1);

		batchVBO = VertexBuffer::Create(&quadVerts[0], sizeof(QuadVertex) * 4);
		instanceVBO = VertexBuffer::Create(sizeof(InstanceData) * MaxQuads);

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

}

void Renderer2D::StartBatch()
{
	if (UseInstancing)
	{
		CurrentInstanceDataPtr = &InstancedData[0];
	}
	else
	{
		CurrentVertexPtr = &verticesBatched[0];
	}
	m_submittedQuads = 0;
}

void Renderer2D::Begin(const glm::mat4& cameraViewProjection)
{
	DrawCall = 0;
	Renderer::Instance().m_cameraBuffer->SetData(&cameraViewProjection,sizeof(glm::mat4));
	StartBatch();
	Renderer::Instance().m_cameraBuffer->Bind();
}


void Renderer2D::DrawQuad(const V5Core::Transform& transform, const glm::vec4& color, Texture2D* texture)
{
	float tIndex = 0.0f;

	if (texture != nullptr)
	{
		bool found = 0;
		for (float i = 0; i < TextureIndex; i++)
		{
			if (texture == AllTextures[(int)i])
			{
				found = 1;
				tIndex = i;
				break;
			}
		}

		if (!found)
		{
			AllTextures[TextureIndex] = texture;
			tIndex = TextureIndex;
			TextureIndex++;
		}
	}

	if (UseInstancing)
	{		
		(*CurrentInstanceDataPtr).ModelMat = transform.GetMatrix();
		(*CurrentInstanceDataPtr).Color = color;
		(*CurrentInstanceDataPtr).TextureIndex = tIndex;
		CurrentInstanceDataPtr++;
	}
	else
	{
		V5_PROFILE_FUNCTION();
		CurrentVertexPtr->Position = transform.GetMatrix() * bl;
		CurrentVertexPtr->Color = color;
		CurrentVertexPtr->UV.x = 0;
		CurrentVertexPtr->UV.y = 0;
		CurrentVertexPtr->TextureIndex = texture == nullptr ? 0.0f : TextureIndex - 1.0f;
		CurrentVertexPtr++;

		CurrentVertexPtr->Position = transform.GetMatrix() * br;
		CurrentVertexPtr->Color = color;
		CurrentVertexPtr->UV.x = 1;
		CurrentVertexPtr->UV.y = 0;
		CurrentVertexPtr->TextureIndex = texture == nullptr ? 0.0f : TextureIndex - 1.0f;
		CurrentVertexPtr++;

		CurrentVertexPtr->Position = transform.GetMatrix() * tr;
		CurrentVertexPtr->Color = color;
		CurrentVertexPtr->UV.x = 1;
		CurrentVertexPtr->UV.y = 1;
		CurrentVertexPtr->TextureIndex = texture == nullptr ? 0.0f : TextureIndex - 1.0f;
		CurrentVertexPtr++;

		CurrentVertexPtr->Position = transform.GetMatrix() * tl;
		CurrentVertexPtr->Color = color;
		CurrentVertexPtr->UV.x = 0;
		CurrentVertexPtr->UV.y = 1;
		CurrentVertexPtr->TextureIndex = texture == nullptr ? 0.0f : TextureIndex - 1.0f;
		CurrentVertexPtr++;

		IndexCount += 6;
	}

	m_submittedQuads++;
	if (m_submittedQuads >= MaxQuads || TextureIndex >= 32)
	{
		FlushBuffer();
	}	
}

void Renderer2D::End()
{

	FlushBuffer();
	//V5CLOG_INFO("Draw calls {0}", DrawCall);
	DrawCall = 0;
}

void Renderer2D::FlushBuffer()
{

	if (m_submittedQuads == 0) return;

	UseInstancing ? ShaderLibrary::GetShader("TextureInstanced").Bind() : ShaderLibrary::GetShader("TextureBatched").Bind();

	//TODO commented to test android
	for (int i = 0; i < TextureIndex; i++)
	{
		AllTextures[i]->Bind(i);
	}


	if (UseInstancing)
	{
		instanceVBO->SetData(&InstancedData[0], sizeof(InstanceData) * m_submittedQuads);

		V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexedInstanced(*vao, m_submittedQuads);
		CurrentInstanceDataPtr = InstancedData;
	}
	else
	{
		V5_PROFILE_FUNCTION();

		batchVBO->SetData(&verticesBatched[0], sizeof(QuadVertexBatched) * m_submittedQuads * 4);

		V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexed(*vao, IndexCount);

		CurrentVertexPtr = verticesBatched;
		IndexCount = 0;
	}
		DrawCall++;
		m_submittedQuads = 0;
		TextureIndex = 1; //Reset to 1 (not 0, slot 0 is alwayys white texture)
	

}

void Renderer2D::Shutdown()
{

}

