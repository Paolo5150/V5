#pragma once
#include <V5/Renderer/Shader.h>


namespace V5Rendering
{
	class OpenGLES2Shader : public Shader
	{
	public:
		static std::unique_ptr<OpenGLES2Shader> FromSource(const std::string& vertSource, const std::string& fragSource);

		OpenGLES2Shader() = default;
		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_shaderID;
	};
}