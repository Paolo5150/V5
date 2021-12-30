#include "Renderer2D.h"
#include "Buffer.h"
#include "Vertex.h"
#include <V5/Renderer/Shader.h>
#include <V5/Components/Components.h>
#include "Renderer.h"
#include <V5/Core/Logger.h>
#include <glm/gtc/type_ptr.hpp>
#include <V5/Debugging/Intrumentor.h>
#include <glm/glm.hpp>

using namespace V5Rendering;
using namespace V5Core;

struct InstanceData
{
	glm::vec3 Color;
	glm::mat4 ModelMat;
};

namespace
{
	bool UseInstancing = 1; // If 1, instancing, if 0, batching
	constexpr uint32_t MaxQuads = 50000;
	std::shared_ptr<VertexArray> vao;
	uint32_t DrawCall = 0;


	// Batching parameters
	uint32_t MaxVertices = MaxQuads * 4;
	uint32_t MaxIndices = MaxQuads * 6;
	std::shared_ptr<VertexBuffer> batchVBO;
	std::shared_ptr<IndexBuffer> batchIBO;
	std::vector<uint32_t> indices;
	uint32_t IndexCount = 0;
	QuadVertex vertices[MaxQuads * 4];

	// Instancing parameters
	InstanceData InstancedData[MaxQuads];
	InstanceData* CurrentInstanceDataPtr;;
	std::shared_ptr<VertexBuffer> instanceVBO;

	glm::vec4 bl = glm::vec4(-0.5, -0.5, 0.0, 1.0);
	glm::vec4 br = glm::vec4(0.5, -0.5, 0.0, 1.0);
	glm::vec4 tr = glm::vec4(0.5, 0.5, 0.0, 1.0);
	glm::vec4 tl = glm::vec4(-0.5, 0.5, 0.0, 1.0);


}

Renderer2D::Renderer2D()
{
	if (!UseInstancing)
	{
		auto layout = BufferLayout({
				BufferElement(ShaderDataType::Float3), // Position
				BufferElement(ShaderDataType::Float3),  // Color
			});


		batchVBO = VertexBuffer::Create(sizeof(QuadVertex) * MaxVertices);

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
		m_cameraBuffer = UniformBuffer::Create(0, sizeof(glm::mat4));

		batchVBO->SetLayout(layout);

		vao = VertexArray::Create();
		vao->AddVertexBuffer(batchVBO);
		vao->SetIndexBuffer(batchIBO);
	}
	else
	{
		auto layout = BufferLayout({
						BufferElement(ShaderDataType::Float3), // Position
						BufferElement(ShaderDataType::Float3),  // Color

			});

		// Need to create 4 vec4s to pass a matrix to the shader via vertex buffer
		auto instancedLayout = BufferLayout({
						BufferElement(ShaderDataType::Float3, false, true),  // Color
						BufferElement(ShaderDataType::Float4, false, true), // Model matrix
						BufferElement(ShaderDataType::Float4, false, true), 
						BufferElement(ShaderDataType::Float4, false, true), 
						BufferElement(ShaderDataType::Float4, false, true), 

			});

		QuadVertex quadVerts[4];
		
		quadVerts[0].Position = glm::vec3(-0.5, -0.5, 0.0);
		quadVerts[0].Color = glm::vec3(0,0,0);

		quadVerts[1].Position = glm::vec3(0.5, -0.5, 0.0);
		quadVerts[1].Color = glm::vec3(0,0,0);

		quadVerts[2].Position = glm::vec3(0.5, 0.5, 0.0);
		quadVerts[2].Color = glm::vec3(0,0,0);

		quadVerts[3].Position = glm::vec3(-0.5, 0.5, 0.0);
		quadVerts[3].Color = glm::vec3(0,0,0);


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
		m_cameraBuffer = UniformBuffer::Create(0, sizeof(glm::mat4));

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
		m_currentVertexPtr = &vertices[0];
	}
	m_submittedQuads = 0;
}

void Renderer2D::Begin(const glm::mat4& cameraViewProjection)
{
	DrawCall = 0;
	m_cameraBuffer->SetData(&cameraViewProjection,sizeof(glm::mat4));
	StartBatch();
	m_cameraBuffer->Bind();
}


void Renderer2D::NextBatch()
{

}

void Renderer2D::DrawQuad(const V5Core::Transform& transform, const glm::vec3& color)
{
	if (UseInstancing)
	{
		(*CurrentInstanceDataPtr).ModelMat = transform.GetMatrix();
		(*CurrentInstanceDataPtr).Color = color;
		CurrentInstanceDataPtr++;
	}
	else
	{
		V5_PROFILE_FUNCTION();
		m_currentVertexPtr->Position = transform.GetMatrix() * bl;
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		m_currentVertexPtr->Position = transform.GetMatrix() * br;
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		m_currentVertexPtr->Position = transform.GetMatrix() * tr;
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		m_currentVertexPtr->Position = transform.GetMatrix() * tl;
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		IndexCount += 6;
	}

	m_submittedQuads++;

	if (m_submittedQuads >= MaxQuads)
	{
		FlushBuffer();
	}
}



void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& color)
{
	if (UseInstancing)
	{
		(*CurrentInstanceDataPtr).ModelMat = glm::translate(glm::mat4(1.0), position);
		(*CurrentInstanceDataPtr).Color = color;
		CurrentInstanceDataPtr++;
	}
	else
	{
		V5_PROFILE_FUNCTION();
		m_currentVertexPtr->Position = glm::vec3(position.x - 0.5f, position.y - 0.5, position.z);
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		m_currentVertexPtr->Position = glm::vec3(position.x + 0.5f, position.y - 0.5, position.z);
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		m_currentVertexPtr->Position = glm::vec3(position.x + 0.5f, position.y + 0.5, position.z);
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		m_currentVertexPtr->Position = glm::vec3(position.x - 0.5f, position.y + 0.5, position.z);
		m_currentVertexPtr->Color = color;
		m_currentVertexPtr++;

		IndexCount += 6;
	}
	
	m_submittedQuads++;

	if (m_submittedQuads >= MaxQuads)
	{
		FlushBuffer();
	}
}

void Renderer2D::End()
{

	FlushBuffer();
	//V5CLOG_INFO("Draw calls {0}", DrawCall);

}

void Renderer2D::FlushBuffer()
{
	if (m_submittedQuads == 0) return;

	ShaderLibrary::GetShader("ColorOnly").Bind();

	if (UseInstancing)
	{
		V5_PROFILE_FUNCTION();

		instanceVBO->SetData(&InstancedData[0], sizeof(InstanceData) * m_submittedQuads);

		V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexedInstanced(*vao, m_submittedQuads);
		CurrentInstanceDataPtr = InstancedData;
	}
	else
	{
		V5_PROFILE_FUNCTION();

		batchVBO->SetData(&vertices[0], sizeof(QuadVertex) * m_submittedQuads * 4);

		V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexed(*vao, IndexCount);

		m_currentVertexPtr = vertices;
		IndexCount = 0;
	}
		DrawCall++;
		m_submittedQuads = 0;
	

}

void Renderer2D::Shutdown()
{

}

