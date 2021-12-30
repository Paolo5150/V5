#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


namespace V5Core
{
	class Transform
	{
	public:
		glm::vec3 Position;
		glm::vec3 Scale;
		glm::vec3 Rotation;

		glm::mat4 GetMatrix() const
		{
			auto rot = glm::toMat4(glm::quat(Rotation));
		
			return glm::translate(glm::mat4(1.0), Position) * rot * glm::scale(glm::mat4(1.0), Scale);
		}
	};
}