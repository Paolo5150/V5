#include "Renderer2D.h"
#include "Buffer.h"
#include "Vertex.h"
#include <V5/Renderer/Shader.h>
#include "Renderer.h"
#include <V5/Core/Logger.h>
#include <glm/gtc/type_ptr.hpp>
#include <V5/Debugging/Intrumentor.h>

using namespace V5Rendering;
using namespace V5Core;

namespace
{
	constexpr uint32_t MaxQuads = 100000;
	uint32_t MaxVertices = MaxQuads * 4;
	uint32_t MaxIndices = MaxQuads * 6;
	std::shared_ptr<VertexBuffer> vbo;
	std::shared_ptr<IndexBuffer> ibo;
	std::shared_ptr<VertexArray> vao;
	std::vector<uint32_t> indices;
	uint32_t IndexCount = 0;
	QuadVertex vertices[MaxQuads * 4];
	uint32_t DrawCall = 0;

	glm::vec3 Positions[MaxQuads];
	glm::vec3* CurrentPositionPtr;
	std::shared_ptr<VertexBuffer> instanceVBO;

	bool UseInstancing = 1;

}

Renderer2D::Renderer2D()
{
	if (!UseInstancing)
	{
		auto layout = BufferLayout({
				BufferElement(ShaderDataType::Float3), // Position
				BufferElement(ShaderDataType::Float3),  // Color
			});


		vbo = VertexBuffer::Create(sizeof(QuadVertex) * MaxVertices);

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

		ibo = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));
		m_cameraBuffer = UniformBuffer::Create(0, sizeof(glm::mat4));

		vbo->SetLayout(layout);

		vao = VertexArray::Create();
		vao->AddVertexBuffer(vbo);
		vao->SetIndexBuffer(ibo);
	}
	else
	{
		auto layout = BufferLayout({
						BufferElement(ShaderDataType::Float3), // Position
						BufferElement(ShaderDataType::Float3),  // Color
			});

		auto instancedLayout = BufferLayout({
						BufferElement(ShaderDataType::Float3, false, true), // Position
			});


		QuadVertex quadVerts[4];
		
		quadVerts[0].Position = glm::vec3(-0.5, -0.5, 0.0);
		quadVerts[0].Color = glm::vec3(1, 0, 0.0);

		quadVerts[1].Position = glm::vec3(0.5, -0.5, 0.0);
		quadVerts[1].Color = glm::vec3(1, 0, 0.0);

		quadVerts[2].Position = glm::vec3(0.5, 0.5, 0.0);
		quadVerts[2].Color = glm::vec3(1, 0, 0.0);

		quadVerts[3].Position = glm::vec3(-0.5, 0.5, 0.0);
		quadVerts[3].Color = glm::vec3(1, 0, 0.0);


		vbo = VertexBuffer::Create(&quadVerts[0], sizeof(QuadVertex) * 4);
		instanceVBO = VertexBuffer::Create(sizeof(glm::vec3) * MaxQuads);

		indices.resize(6);
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		ibo = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));
		m_cameraBuffer = UniformBuffer::Create(0, sizeof(glm::mat4));

		vbo->SetLayout(layout);
		instanceVBO->SetLayout(instancedLayout);

		vao = VertexArray::Create();
		vao->AddVertexBuffer(vbo);
		vao->AddVertexBuffer(instanceVBO);
		vao->SetIndexBuffer(ibo);
	}
	
}

void Renderer2D::StartBatch()
{
	if (UseInstancing)
	{
		CurrentPositionPtr = &Positions[0];
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


void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& color)
{
	if (UseInstancing)
	{
		*CurrentPositionPtr = position;
		CurrentPositionPtr++;
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
		instanceVBO->SetData(&Positions[0], sizeof(glm::vec3) * m_submittedQuads);
		V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexedInstanced(*vao, m_submittedQuads);
		CurrentPositionPtr = Positions;
	}
	else
	{
		V5_PROFILE_FUNCTION();

		vbo->SetData(&vertices[0], sizeof(QuadVertex) * m_submittedQuads * 4);

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

