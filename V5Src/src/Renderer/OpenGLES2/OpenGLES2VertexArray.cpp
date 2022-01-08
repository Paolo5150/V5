#include "OpenGLES2VertexArray.h"
#include <glad/gles2.h>
#include "Renderer/Buffer.h"
#include <V5/Debugging/Intrumentor.h>
#include <V5/Core/Logger.h>
using namespace V5Rendering;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return GL_FLOAT;
	case ShaderDataType::Float2:   return GL_FLOAT;
	case ShaderDataType::Float3:   return GL_FLOAT;
	case ShaderDataType::Float4:   return GL_FLOAT;
	case ShaderDataType::Mat3:     return GL_FLOAT;
	case ShaderDataType::Mat4:     return GL_FLOAT;
	case ShaderDataType::Int:      return GL_INT;
	case ShaderDataType::Int2:     return GL_INT;
	case ShaderDataType::Int3:     return GL_INT;
	case ShaderDataType::Int4:     return GL_INT;
	case ShaderDataType::Bool:     return GL_BOOL;
	}

	return 0;
}


OpenGLES2VertexArray::OpenGLES2VertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayID);// This is the way.

}

OpenGLES2VertexArray::~OpenGLES2VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}


void OpenGLES2VertexArray::Bind() const
{
	glBindVertexArray(m_vertexArrayID);
	for (size_t i = 0; i < m_locationIndex; i++)
	{
		glEnableVertexAttribArray(i);

	}
}

void OpenGLES2VertexArray::Unbind() const
{
	glBindVertexArray(0);

}

void OpenGLES2VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vb)
{
	Bind();
	vb->Bind();
	const auto& layout = vb->GetLayout();

	for (const auto& element : layout.GetBufferElements())
	{
		glVertexAttribPointer(m_locationIndex,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.DataType),
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.Offset);

		if (element.Instanced)
			glVertexAttribDivisor(m_locationIndex, 1);

		m_locationIndex++;
	}

	m_vertexBuffers.push_back(vb);
}

void OpenGLES2VertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> ib)
{
	m_indexBuffer = ib;
}
