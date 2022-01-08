#include "OpenGLES2Buffer.h"
#include <iostream>
#include <glad/gles2.h>
#include <V5/Core/Logger.h>

using namespace V5Rendering;

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(uint32_t size)
{
	glGenBuffers(1, &m_bufferID);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(const void* data, uint32_t size)
{
	glGenBuffers(1, &m_bufferID);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLES2VertexBuffer::~OpenGLES2VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}


void OpenGLES2VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

void OpenGLES2VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLES2VertexBuffer::SetLayout(const BufferLayout& layout)
{
	m_layout = layout;
}
const BufferLayout& OpenGLES2VertexBuffer::GetLayout()
{
	return m_layout;
}

void OpenGLES2VertexBuffer::SetData(const void* data, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


//********** Index Buffer **********//

OpenGLES2IndexBuffer::OpenGLES2IndexBuffer(uint32_t* data, uint32_t count) : m_count(count)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

OpenGLES2IndexBuffer::~OpenGLES2IndexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void OpenGLES2IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}
void OpenGLES2IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLES2IndexBuffer::GetCount() const
{
	return m_count;
}

//********** Uniform Buffer **********//

OpenGLES2UniformBuffer::OpenGLES2UniformBuffer(uint32_t binding, uint32_t size) :
	m_binding(binding)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, binding, m_bufferID, 0, size);


}

OpenGLES2UniformBuffer::OpenGLES2UniformBuffer(uint32_t binding, const void* data, uint32_t size) :
	m_binding(binding)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, binding, m_bufferID, 0, size);
}

OpenGLES2UniformBuffer::~OpenGLES2UniformBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void OpenGLES2UniformBuffer::Bind(uint32_t shaderID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glUniformBlockBinding(shaderID, 0, 0); //TODO, set appropriate bindings
}

void OpenGLES2UniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
}

void OpenGLES2UniformBuffer::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLES2UniformBuffer::SetData(const void* data, uint32_t size)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);

}

OpenGLES2UniformBuffer::OpenGLES2UniformBuffer(std::string uniformName, uint32_t size)
{

}
OpenGLES2UniformBuffer::OpenGLES2UniformBuffer(std::string uniformName, const void* data, uint32_t size)
{

}
