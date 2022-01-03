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


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* data, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetCount() const override;

	private:
		uint32_t m_bufferID;
		uint32_t m_count;
	};

	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32_t binding, uint32_t size);
		OpenGLUniformBuffer(uint32_t binding, const void* data, uint32_t size);
		~OpenGLUniformBuffer();

		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* data, uint32_t size) override;
		uint32_t GetBinding() const { return m_binding; }
		virtual uint32_t GetID() const override { return m_bufferID; }

	private:
		uint32_t m_bufferID;
		uint32_t m_binding;
		BufferLayout m_layout;
	};
}