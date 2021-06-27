#pragma once
#include "Renderer/VertexArray.h"
#include <vector>

namespace V5Rendering
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		~OpenGLVertexArray();
		OpenGLVertexArray();
		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(std::shared_ptr<VertexBuffer> vb) override;
		void SetIndexBuffer(std::shared_ptr<IndexBuffer> ib) override;

		std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override { return m_vertexBuffers; };
		std::shared_ptr<IndexBuffer>& GetIndexBuffer() override { return m_indexBuffer; };
	private:
		uint32_t m_vertexArrayID;
		uint32_t m_locationIndex = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer; //TODO: vector of these...?
	};
}

