#include "OpenGLES2Shader.h"
#include <fstream>
#include <Core/CoreLogger.h>
#include <glad/gles2.h>
#include <sstream>

using namespace V5Rendering;

OpenGLES2Shader::OpenGLES2Shader(const std::string vert, const std::string frag)
{
	char buf[1024];
	getcwd(buf, 1024);

	V5LOG_INFO("Working dir {0}", buf);

	//Load SPIR-V shaders
	unsigned int vertex, fragment;

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vert);
		fShaderFile.open(frag);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	{
		glShaderSource(vertex, 1, (const GLchar* const*)vertexCode.c_str(), NULL);
		glCompileShader(vertex);

		// Check for success/failure
		GLint status;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
		if (GL_FALSE == status)
		{
			V5LOG_ERROR("Failed to load vertex shader");
		}
	}


	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, (const GLchar* const*)fragmentCode.c_str(), NULL);
	glCompileShader(fragment);

	// Check for success/failure
	GLint status;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
	if (GL_FALSE == status)
	{
		V5LOG_ERROR("Failed to load fragment shader");
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
		V5LOG_ERROR("Failed to load vertex shader");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glUseProgram(m_shaderID);
}
void OpenGLES2Shader::Bind() const
{
	glUseProgram(m_shaderID);

}

void OpenGLES2Shader::Unbind() const
{
	glUseProgram(0);

}