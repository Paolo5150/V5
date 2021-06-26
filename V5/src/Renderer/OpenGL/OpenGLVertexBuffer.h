#pragma once
#include "Renderer/Buffer.h"


namespace V5Rendering
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(const void* data, uint32_t size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* data, uint32_t size) override;
		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() override;
		virtual uint32_t GetID() const override { return m_bufferID; }


	private:
		uint32_t m_bufferID;
		BufferLayout m_layout;
	};
}