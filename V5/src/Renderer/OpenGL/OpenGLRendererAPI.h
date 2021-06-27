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

		void SetClearColor(float r, float g, float b, float a) const override;
		void SetViewport(float x, float y, float width, float height) const override;


	};
}