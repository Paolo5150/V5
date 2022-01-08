#include "OpenGLVertexArray.h"
#include <glad/gl.h>
#include "Renderer/Buffer.h"
#include <V5/Debugging/Intrumentor.h>
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


OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &m_vertexArrayID);// This is the way.

}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}


void OpenGLVertexArray::Bind() const
{
	V5_PROFILE_FUNCTION();
	glBindVertexArray(m_vertexArrayID);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);

}

void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vb)
{
	Bind();
	vb->Bind();
	const auto& layout = vb->GetLayout();

	for (const auto& element : layout.GetBufferElements())
	{
		//glEnableVertexArrayAttrib(m_vertexArrayID, m_locationIndex);// Need to precise vao, as there is no context binding in DSA style
		//glVertexArrayAttribFormat(m_vertexArrayID, m_locationIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.DataType), element.Normalized, element.Offset);// Need to precise vao, as there is no context binding in DSA
		//glVertexArrayAttribBinding(m_vertexArrayID, m_locationIndex, m_vertexBuffers.size());
		//if (element.Instanced)
		//	glVertexAttribDivisor(m_vertexBuffers.size(), 1);
		//m_locationIndex++;

		glEnableVertexAttribArray(m_locationIndex);
		glVertexAttribPointer(m_locationIndex,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.DataType),
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.Offset);

		if(element.Instanced)
			glVertexAttribDivisor(m_locationIndex, 1);

		m_locationIndex++;
	}

	m_vertexBuffers.push_back(vb);
}

void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> ib)
{
	m_indexBuffer = ib;
}
