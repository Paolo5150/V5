#include "Shader.h"
#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"

using namespace V5Rendering;

std::unique_ptr<Shader> Shader::CreateFromSPIRV(const std::string vert, const std::string frag)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL:
		return std::make_unique< OpenGLShader>(vert, frag);
	default:
		break;
	}
}
