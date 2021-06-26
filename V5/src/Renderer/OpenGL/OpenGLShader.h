#pragma once
#include "Renderer/Shader.h"


namespace V5Rendering
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string vert, const std::string frag);
		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_shaderID;
	};
}