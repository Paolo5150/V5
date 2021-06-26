#pragma once
#include <iostream>

namespace V5Core
{
	class Event;
}

namespace V5Rendering
{
	class RendererAPI
	{
	public:
		enum class API
		{
			OpenGL
		};

		virtual ~RendererAPI() = default;
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void OnEvent(V5Core::Event& e) = 0;
		static std::unique_ptr<RendererAPI> Create();
		static API GetAPI() { return s_API; }
	private:
		static API s_API;

	};
}