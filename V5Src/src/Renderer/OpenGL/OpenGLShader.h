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
		uint32_t GetNativeID() override { return m_shaderID; }

		void Bind() const override;
		void Unbind() const override;
		int GetAttribLocation(std::string attribName) override;
		int GetUBOLocation(std::string attribName) override { return -1; }; // TODO: implement ?

	private:
		uint32_t m_shaderID;
	};
}