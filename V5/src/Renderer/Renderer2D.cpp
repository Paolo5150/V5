#include "Renderer2D.h"
#include "Buffer.h"
#include "Vertex.h"
#include <V5/Renderer/Shader.h>
#include "Renderer.h"
#include <V5/Core/Logger.h>

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

void Renderer2D::Begin()
{
	StartBatch();
}


void Renderer2D::NextBatch()
{

}


void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& color)
{
	m_currentVertexPtr->Position = position - glm::vec3(-0.5f, -0.5, 0.0);
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;

	m_currentVertexPtr->Position = position - glm::vec3(0.5f, -0.5, 0.0);
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;

	m_currentVertexPtr->Position = position - glm::vec3(0.5f, 0.5, 0.0);
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;

	m_currentVertexPtr->Position = position - glm::vec3(-0.5f, 0.5, 0.0);
	m_currentVertexPtr->Color = color;
	m_currentVertexPtr++;	

	m_submittedQuads++;

	if (m_submittedQuads >= MaxQuads)
	{
		FlushBuffer();
	}
}

void Renderer2D::FlushBuffer()
{
	ShaderLibrary::GetShader("ColorOnly").Bind();
	vbo->SetData(m_quadVerticesArray.data(), sizeof(QuadVertex) * 4);
	V5Rendering::Renderer::Instance().GetRenderAPI().RenderIndexed(*vao);
	m_submittedQuads = 0;

}

void Renderer2D::Shutdown()
{

}

