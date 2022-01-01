#pragma once
#include<glm/glm.hpp>
#include "VertexArray.h"
#include <V5/Renderer/IRenderer2D.h>
#include <V5/Components/Components.h>
#include <vector>
#include "Buffer.h"

struct QuadVertex
{
	glm::vec3 Position;
	glm::vec2 UV;
};

struct QuadVertexBatched
{
	glm::vec3 Position;
	glm::vec2 UV;
	glm::vec4 Color;
	float TextureIndex;
};

namespace V5Rendering
{
	class Renderer2D : public IRenderer2D
	{
	public:
		Renderer2D();
		void Shutdown();
		void DrawQuad(const V5Core::Transform& transform, const glm::vec4& color, std::shared_ptr<Texture2D> texture = nullptr) override;

		void FlushBuffer();
		void Begin(const glm::mat4& cameraViewProjection) override;
		void End() override;
	private:
		void StartBatch();
		QuadVertexBatched* m_currentVertexPtr;
		uint32_t m_currentQuadCount;
		uint32_t m_submittedQuads;
		std::shared_ptr<UniformBuffer> m_cameraBuffer;

		glm::mat4 const* m_currentViewProjection;

	};
}
