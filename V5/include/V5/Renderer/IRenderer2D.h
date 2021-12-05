#pragma once
#include <glm/glm.hpp>

namespace V5Rendering
{
	class IRenderer2D
	{
	public:

		virtual void DrawQuad(const glm::vec3& position, const glm::vec3& color) = 0;
		virtual void Begin() = 0;

	};
}