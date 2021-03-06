#pragma once
#include <iostream>

namespace V5Core
{
	class Event;
}

namespace V5Rendering
{
	class VertexArray;

	class RendererAPI
	{
	public:
		enum class API
		{
			OpenGL,
			OpenGLES,
			Vulkan
		};

		virtual ~RendererAPI() = default;
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void OnEvent(V5Core::Event& e) = 0;

		virtual void SetClearColor(float r, float g, float b, float a) const = 0;
		virtual void SetViewport(int x, int y, int width, int height) const = 0;
		virtual void SetDepthTestEnabled(bool enabled) = 0;
		virtual void SetCullEnabled(bool enabled) = 0;

		virtual void RenderIndexed(VertexArray& ar) = 0;
		virtual void RenderIndexed(VertexArray& aroverride, uint32_t indexCount) = 0;
		virtual void RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount) = 0;


		virtual void Clear() = 0;


		static std::unique_ptr<RendererAPI> Create();
		static API GetAPI() { return s_API; }
	private:
		static API s_API;

	};
}