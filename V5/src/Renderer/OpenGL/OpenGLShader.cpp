#include "OpenGLShader.h"
#include <fstream>
#include <Core/CoreLogger.h>

using namespace V5Rendering;

OpenGLShader::OpenGLShader(const std::string vert, const std::string frag)
{
	//Load SPIR-V shaders

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	{
		// Load the shader into a std::vector
		std::ifstream inStream("Assets\\Shaders\\colorOnly.vert.spv", std::ios::binary);
		std::istreambuf_iterator<char> startIt(inStream), endIt;
		std::vector<char> buffer(startIt, endIt);
		inStream.close();

		// Load using glShaderBinary
		glShaderBinary(1, &vertShader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), buffer.size());

		// Specialize the shader (specify the entry point)
		glSpecializeShader(vertShader, "main", 0, 0, 0);

		// Check for success/failure
		GLint status;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
		if (GL_FALSE == status)
		{
			V5CLOG_ERROR("Failed to load vertex shader");
		}

	}


	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the shader into a std::vector
	std::ifstream inStream("Assets\\Shaders\\colorOnly.frag.spf", std::ios::binary);
	std::istreambuf_iterator<char> startIt(inStream), endIt;
	std::vector<char> buffer(startIt, endIt);
	inStream.close();

	// Load using glShaderBinary
	glShaderBinary(1, &fragShader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), buffer.size());

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
	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertShader);
	glAttachShader(m_shaderID, fragShader);
	glLinkProgram(m_shaderID);

	GLint isLinked = 0;
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		V5LOG_CRITICAL("Failed to link shader");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glUseProgram(m_shaderID);
}
void OpenGLShader::Bind() const
{
	glUseProgram(m_shaderID);

}

void OpenGLShader::Unbind() const
{
	glUseProgram(0);

}