#pragma once
#include "Renderer/RendererAPI.h"

namespace V5Rendering
{
	class OpenGLES2RendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void Shutdown() override;
		void OnEvent(V5Core::Event& e) override;

		void SetClearColor(float r, float g, float b, float a) const override;
		void SetViewport(int x, int y, int width, int height) const override;
		void RenderIndexed(VertexArray& aroverride) override;
		void RenderIndexed(VertexArray& aroverride, uint32_t indexCount) override;
		void RenderIndexedInstanced(VertexArray& vao, uint32_t instanceCount) override;

		void Clear() override;

	};
}