#pragma once
#include <V5/Renderer/Shader.h>


namespace V5Rendering
{
	class OpenGLES2Shader : public Shader
	{
	public:
		OpenGLES2Shader(const std::string vert, const std::string frag);
		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_shaderID;
	};
}