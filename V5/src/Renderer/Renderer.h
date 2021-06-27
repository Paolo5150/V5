#pragma once

#include "RendererAPI.h"

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

	private:
		static std::unique_ptr<Renderer> s_Instance;
		std::unique_ptr<RendererAPI> m_renderAPI;

	};
}