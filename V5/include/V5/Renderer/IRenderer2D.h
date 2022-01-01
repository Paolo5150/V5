#pragma once
#include <glm/glm.hpp>

namespace V5Core
{
	class Transform;
}

namespace V5Rendering
{
	class Texture2D;

	class IRenderer2D
	{
	public:

		virtual void DrawQuad(const V5Core::Transform& transform, const glm::vec4& color, std::shared_ptr<Texture2D> texture = nullptr) = 0;

		virtual void Begin(const glm::mat4& cameraViewProjection) = 0;
		virtual void End() = 0;

	};
}