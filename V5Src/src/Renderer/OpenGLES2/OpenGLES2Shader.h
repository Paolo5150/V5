#pragma once
#include <V5/Renderer/Shader.h>


namespace V5Rendering
{
	class OpenGLES2Shader : public Shader
	{
	public:
		static std::unique_ptr<OpenGLES2Shader> FromSource(const std::string& vertSource, const std::string& fragSource);

		OpenGLES2Shader() = default;
		uint32_t GetNativeID() override { return m_shaderID; }

		void Bind() const override;
		void Unbind() const override;
		int GetAttribLocation(std::string attribName) override;
		int GetUBOLocation(std::string attribName) override;

	private:
		uint32_t m_shaderID;
	};
}