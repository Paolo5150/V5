#pragma once
#include<glm/glm.hpp>
#include "VertexArray.h"
#include <V5/Renderer/IRenderer2D.h>
#include <V5/Components/Components.h>
#include <vector>
#include "Buffer.h"



namespace V5Rendering
{
	class TileRenderer2D
	{
	public:
		TileRenderer2D();
		void Shutdown();
		void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color, Texture2D* texture);

		void FlushBuffer();
		void Begin(const glm::mat4& cameraViewProjection);
		void End();
		void StartBatch();

		uint32_t m_submittedQuads;

		glm::mat4 const* m_currentViewProjection;


	};
}
