#include "OpenGLES2Shader.h"
#include <fstream>
#include <Core/CoreLogger.h>
#include <glad/gles2.h>
#include <sstream>

using namespace V5Rendering;

std::unique_ptr<OpenGLES2Shader> OpenGLES2Shader::FromSource(const std::string& vertSource, const std::string& fragSource)
{
	std::unique_ptr<OpenGLES2Shader> theShader = std::make_unique<OpenGLES2Shader>();

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	{
		if (fragShader == 0)
		{
			V5LOG_ERROR("Failed to create shader ID");

		}
		char const* sourcePointer = fragSource.c_str();

		glShaderSource(fragShader, 1, &sourcePointer, NULL);
		glCompileShader(fragShader);

		// Check Shader
		GLint result = GL_FALSE;
		int infoLogLength;

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (result == 0)
		{
			std::vector<char> shaderErrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(fragShader, infoLogLength, NULL, &shaderErrorMessage[0]);
			V5LOG_ERROR("Failed to compile fragment shader: {0}", shaderErrorMessage.data());
		}
	}

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	{
		if (vertShader == 0)
		{
			V5LOG_ERROR("Failed to create shader ID");

		}
		char const* sourcePointer = vertSource.c_str();

		glShaderSource(vertShader, 1, &sourcePointer, NULL);
		glCompileShader(vertShader);

		// Check Shader
		GLint result = GL_FALSE;
		int infoLogLength;

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (result == 0)
		{
			std::vector<char> shaderErrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(vertShader, infoLogLength, NULL, &shaderErrorMessage[0]);
			V5LOG_ERROR("Failed to compile vertex shader: {0}", shaderErrorMessage.data());
		}
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
		V5LOG_ERROR("Failed to create shader program");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glUseProgram(theShader->m_shaderID);

	return theShader;
}

void OpenGLES2Shader::Bind() const
{
	glUseProgram(m_shaderID);

}

void OpenGLES2Shader::Unbind() const
{
	glUseProgram(0);

}