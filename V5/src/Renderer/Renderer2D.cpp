#include "Renderer2D.h"
#include "Buffer.h"
#include "Vertex.h"
#include <V5/Renderer/Shader.h>
#include "Renderer.h"
#include <V5/Core/Logger.h>
#include <glm/gtc/type_ptr.hpp>

using namespace V5Rendering;
using namespace V5Core;

namespace
{
	uint32_t MaxQuads = 1;
	std::shared_ptr<VertexBuffer> vbo;
	std::shared_ptr<IndexBuffer> ibo;
	std::shared_ptr<VertexArray> vao;


}

Renderer2D::Renderer2D()
{

	auto layout = BufferLayout({
				BufferElement(ShaderDataType::Float3), // Position
				BufferElement(ShaderDataType::Float3),  // Color
		});

	std::vector<uint32_t> indices = { 0,1,2, 2, 3, 0 };
	vbo = VertexBuffer::Create(sizeof(QuadVertex) * 4);

	ibo = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));

	m_cameraBuffer = UniformBuffer::Create(0,sizeof(glm::mat4));

	m_quadVerticesArray.resize(4); // 1 quad for now

	vbo->SetLayout(layout);

	vao = VertexArray::Create();
	vao->AddVertexBuffer(vbo);
	vao->SetIndexBuffer(ibo);
}

void Renderer2D::StartBatch()
{
	m_currentVertexPtr = &m_quadVerticesArray[0];
	m_submittedQuads = 0;
}

void Renderer2D::Begin(const glm::mat4& cameraViewProjection)
{
	m_cameraBuffer->SetData(&cameraViewProjection,sizeof(glm::mat4));
	StartBatch();
}


void Renderer2D::NextBatch()
{

}


void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& color)
{
	m_currentVertexPtr->Position = glm::vec3(position.x - 0.5f, position.y -0.5, position.z);
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;

	m_currentVertexPtr->Position = glm::vec3(position.x + 0.5f, position.y - 0.5, position.z  );
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;

	m_currentVertexPtr->Position =glm::vec3(position.x + 0.5f, position.y + 0.5, position.z );
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;

	m_currentVertexPtr->Position =  glm::vec3(position.x - 0.5f, position.y + 0.5, position.z);
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;	

	m_submittedQuads++;

	if (m_submittedQuads >= MaxQuads)
	{
		FlushBuffer();
	}
}

void Renderer2D::End()
{
	FlushBuffer();
}

void Renderer2D::FlushBuffer()
{
	if (m_submittedQuads == 0) return;

	ShaderLibrary::GetShader("ColorOnly").Bind();
	vbo->SetData(m_quadVerticesArray.data(), sizeof(QuadVertex) * 4);
	m_cameraBuffer->Bind();

	V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexed(*vao);
	m_submittedQuads = 0;
	m_currentVertexPtr = &m_quadVerticesArray[0];

}

void Renderer2D::Shutdown()
{

}

