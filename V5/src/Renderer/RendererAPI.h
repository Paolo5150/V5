#pragma once
#include <iostream>

#define G_API VULKAN

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
			Vulkan
		};

		virtual ~RendererAPI() = default;
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void OnEvent(V5Core::Event& e) = 0;

		virtual void SetClearColor(float r, float g, float b, float a) const = 0;
		virtual void SetViewport(float x, float y, float width, float height) const = 0;
		virtual void RenderIndexed(VertexArray& ar) = 0;
		virtual void Clear() = 0;


		static std::unique_ptr<RendererAPI> Create();
		static API GetAPI() { return s_API; }
	private:
		static API s_API;

	};
}