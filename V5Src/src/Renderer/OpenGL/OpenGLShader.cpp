#include "OpenGLShader.h"
#include <fstream>
#include <Core/CoreLogger.h>
#include <glad/gl.h>

using namespace V5Rendering;

std::unique_ptr<OpenGLShader> OpenGLShader::FromSPIRV(const std::vector<char>& vertBinary, const std::vector<char>& fragBinary)
{
	std::unique_ptr<OpenGLShader> theShader = std::make_unique<OpenGLShader>();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	{
		// Load using glShaderBinary
		glShaderBinary(1, &vertShader, GL_SHADER_BINARY_FORMAT_SPIR_V, vertBinary.data(), vertBinary.size());

		// Specialize the shader (specify the entry point)
		glSpecializeShader(vertShader, "main", 0, 0, 0);

		// Check for success/failure
		GLint status;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
		if (GL_FALSE == status)
		{
			V5CLOG_ERROR("Failed to load vertex shader");
			V5LOG_ERROR("Failed to load vertex shader");
		}

	}


	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load using glShaderBinary
	glShaderBinary(1, &fragShader, GL_SHADER_BINARY_FORMAT_SPIR_V, fragBinary.data(), fragBinary.size());

	// Specialize the shader (specify the entry point)
	glSpecializeShader(fragShader, "main", 0, 0, 0);

	// Check for success/failure
	GLint status;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
	if (GL_FALSE == status)
	{
		V5CLOG_ERROR("Failed to load fragment shader");
	}

	//Links
	theShader->m_shaderID = glCreateProgram();
	glAttachShader(theShader->m_shaderID, vertShader);
	glAttachShader(theShader->m_shaderID, fragShader);
	glLinkProgram(theShader->m_shaderID);

	GLint isLinked = 0;
	glGetProgramiv(theShader->m_shaderID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		V5CLOG_ERROR("Failed to load fragment shader");
		V5LOG_ERROR("Failed to load vertex shader");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glUseProgram(theShader->m_shaderID);

	return theShader;
}

int OpenGLShader::GetAttribLocation(std::string attribName)
{
	return glGetAttribLocation(m_shaderID, attribName.c_str());
}

void OpenGLShader::Bind() const
{
	glUseProgram(m_shaderID);

}

void OpenGLShader::Unbind() const
{
	glUseProgram(0);

}