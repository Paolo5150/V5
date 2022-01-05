#pragma once
#include "Renderer/Buffer.h"


namespace V5Rendering
{
	class OpenGLES2VertexBuffer : public VertexBuffer
	{
	public:
		OpenGLES2VertexBuffer(uint32_t size);
		OpenGLES2VertexBuffer(const void* data, uint32_t size);
		~OpenGLES2VertexBuffer();

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


	class OpenGLES2IndexBuffer : public IndexBuffer
	{
	public:
		OpenGLES2IndexBuffer(uint32_t* data, uint32_t count);
		~OpenGLES2IndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetCount() const override;

	private:
		uint32_t m_bufferID;
		uint32_t m_count;
	};

	class OpenGLES2UniformBuffer : public UniformBuffer
	{
	public:
		OpenGLES2UniformBuffer(uint32_t binding, uint32_t size);
		OpenGLES2UniformBuffer(uint32_t binding, const void* data, uint32_t size);
		~OpenGLES2UniformBuffer();

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