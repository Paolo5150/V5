#pragma once

#include <glad/glad.h>
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

		static std::unique_ptr<Shader> CreateFromSPIRV(const std::string vert, const std::string frag);

	};

	class ShaderLibrary
	{
	public:
		void Add(std::string, std::unique_ptr<Shader>);

	private:
		std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaderMap;

	};
}
