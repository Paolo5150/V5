#pragma once

#include "RendererAPI.h"
#include "Renderer2D.h"
#include "TileRenderer2D.h"
#include <V5/Renderer/IRenderer.h>

namespace V5Core
{
	class Event;
}


namespace V5Rendering
{
	class Renderer : public IRenderer
	{
		friend class Core;
		friend class Renderer2D;
		friend class TileRenderer2D;

	public:
		static Renderer& Instance();

		RendererAPI& GetRenderAPI() { return *m_renderAPI; }
		void Init();
		void Render();
		void Shutdown();
		void OnEvent(V5Core::Event& e);
		Renderer2D& GetRenderer2D() override { return *m_renderer2D; }
		TileRenderer2D& GetTileRenderer2D() { return *m_tileRenderer2D; }

	private:
		static std::unique_ptr<Renderer> s_Instance;
		std::unique_ptr<RendererAPI> m_renderAPI;
		std::unique_ptr<Renderer2D> m_renderer2D;
		std::unique_ptr<TileRenderer2D> m_tileRenderer2D;
		std::shared_ptr<UniformBuffer> m_cameraBuffer;


	};
}