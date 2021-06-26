#pragma once
#include "Renderer/RendererAPI.h"

namespace V5Rendering
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void Shutdown() override;
		void OnEvent(V5Core::Event& e) override;


	};
}