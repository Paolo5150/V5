#pragma once

#include "RendererAPI.h"
#include "Renderer2D.h"

namespace V5Core
{
	class Event;
}


namespace V5Rendering
{
	class Renderer
	{
		friend class Core;
	public:
		static Renderer& Instance();

		RendererAPI& GetRenderAPI() { return *m_renderAPI; }
		void Init();
		void Render();
		void Shutdown();
		void OnEvent(V5Core::Event& e);
		Renderer2D& GetRenderer2D() { return *m_renderer2D; }

	private:
		static std::unique_ptr<Renderer> s_Instance;
		std::unique_ptr<RendererAPI> m_renderAPI;
		std::unique_ptr<Renderer2D> m_renderer2D;

	};
}