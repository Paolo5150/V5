#pragma once

#include <iostream>
#include <unordered_map>

namespace V5Rendering
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetNativeID() = 0;

		static std::unique_ptr<Shader> CreateFromSPIRV(const std::string vert, const std::string frag);
		static std::unique_ptr<Shader> CreateFromSource(const std::string vert, const std::string frag);
		virtual int GetAttribLocation(std::string attribName) = 0;
		virtual int GetUBOLocation(std::string attribName) = 0;

	};

	class ShaderLibrary
	{
	public:
		static void Add(std::string, std::unique_ptr<Shader>);
		static Shader& GetShader(std::string name);
		static void Shutdown() { m_shaderMap.clear(); };

	private:
		static std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaderMap;

	};
}
