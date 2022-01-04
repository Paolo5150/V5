#include "OpenGLBuffer.h"
#include <iostream>
#include <glad/gl.h>
#include <Core/CoreLogger.h>
#include <V5/Debugging/Intrumentor.h>

using namespace V5Rendering;

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
	glCreateBuffers(1, &m_bufferID);//uses DSA. This is the way.

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t size)
{
	glCreateBuffers(1, &m_bufferID);//uses DSA. This is the way.

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}


void OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

void OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
{
	m_layout = layout;
}
const BufferLayout& OpenGLVertexBuffer::GetLayout()
{
	return m_layout;
}

void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
{
	V5_PROFILE_FUNCTION();

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


//********** Index Buffer **********//

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t count) : m_count(count)
{
	glCreateBuffers(1, &m_bufferID);

	glNamedBufferStorage(m_bufferID, count * sizeof(uint32_t), data, 0);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void OpenGLIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}
void OpenGLIndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::GetCount() const
{
	return m_count;
}

//********** Uniform Buffer **********//

OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t binding, uint32_t size) :
	m_binding(binding)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glNamedBufferStorage(m_bufferID, size, NULL, GL_DYNAMIC_STORAGE_BIT);
	glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, m_bufferID);

}

OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t binding, const void* data, uint32_t size) :
	m_binding(binding)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glNamedBufferStorage(m_bufferID, size, data, 0); // Flag 0 means static data, cannot be changed
	glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, m_bufferID);
}

OpenGLUniformBuffer::~OpenGLUniformBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}


void OpenGLUniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);

}

void OpenGLUniformBuffer::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLUniformBuffer::SetData(const void* data, uint32_t size)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
}
