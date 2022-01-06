#pragma once
#include <V5/Renderer/Shader.h>
#include <vector>

namespace V5Rendering
{
	class OpenGLShader : public Shader
	{
	public:
		static std::unique_ptr<OpenGLShader> FromSPIRV(const std::vector<char>& vertBinary, const std::vector<char>& fragBinary);
		OpenGLShader() = default;
		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_shaderID;
	};
}