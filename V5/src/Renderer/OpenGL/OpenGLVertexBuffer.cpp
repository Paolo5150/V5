#include "OpenGLVertexBuffer.h"
#include <iostream>
#include <glad/glad.h>
#include <Core/CoreLogger.h>

using namespace V5Rendering;

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
	glCreateBuffers(1, &m_bufferID);//uses DSA. This is the way.

	glNamedBufferStorage(m_bufferID, size, NULL, GL_DYNAMIC_STORAGE_BIT);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t size)
{
	glCreateBuffers(1, &m_bufferID);//uses DSA. This is the way.

	glNamedBufferStorage(m_bufferID, size, data, 0); // Flag 0 means static data, cannot be changed
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
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}