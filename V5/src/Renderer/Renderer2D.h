#pragma once
#include<glm/glm.hpp>
#include "VertexArray.h"
#include <V5/Renderer/IRenderer2D.h>
#include <vector>

struct QuadVertex
{
	glm::vec3 Position;
	glm::vec3 Color;
};

namespace V5Rendering
{
	class Renderer2D : public IRenderer2D
	{
	public:
		Renderer2D();
		void Shutdown();
		void DrawQuad(const glm::vec3& position, const glm::vec3& color) override;
		void FlushBuffer();
		void Begin() override;
	private:
		void StartBatch();
		void NextBatch();
		QuadVertex* m_currentVertexPtr;
		uint32_t m_currentQuadCount;
		std::vector<QuadVertex> m_quadVerticesArray;
		std::vector<uint32_t> m_quadIndices;
		uint32_t m_submittedQuads;

	};
}