#include <V5/Renderer/Shader.h>
#include "Renderer.h"
#include "Core/CoreLogger.h"
#ifdef V5_PLATFORM_WINDOWS
#include "OpenGL/OpenGLShader.h"
#endif
#ifdef V5_PLATFORM_ANDROID
#include "OpenGLES2/OpenGLES2Shader.h"
#endif

using namespace V5Rendering;

std::unordered_map<std::string, std::unique_ptr<Shader>> ShaderLibrary::m_shaderMap;

std::unique_ptr<Shader> Shader::CreateFromSPIRV(const std::string vert, const std::string frag)
{
	switch (RendererAPI::GetAPI())
	{
#ifdef V5_PLATFORM_WINDOWS
	case RendererAPI::API::OpenGL:
		return std::make_unique< OpenGLShader>(vert, frag);
#endif
#ifdef V5_PLATFORM_ANDROID
	case RendererAPI::API::OpenGLES:
		return std::make_unique< OpenGLES2Shader>(vert, frag);
#endif

	default:
		break;
	}
}


void ShaderLibrary::Add(std::string name, std::unique_ptr<Shader> shader)
{
	auto it = m_shaderMap.find(name);
	if (it != m_shaderMap.end())
	{
		V5CLOG_WARN("Shader {0} already in shader library, will overwrite", name);
	}

	m_shaderMap[name] = std::move(shader);
}

Shader& ShaderLibrary::GetShader(std::string name)
{
	auto it = m_shaderMap.find(name);
	if (it == m_shaderMap.end())
	{
		V5CLOG_CRITICAL("Trying to access shader {0}, which does not exist. Throwing exception", name);
		throw std::runtime_error("The shader you're trying to access does not exist");
	}

	return *m_shaderMap[name];
}

