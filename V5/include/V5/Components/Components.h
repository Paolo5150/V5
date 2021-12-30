#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


namespace V5Core
{
	class Transform
	{
	public:
		Transform()
		{
			m_scale = glm::vec3(1, 1, 1 );
			UpdateMatrix();
		}

		void SetPosition(const glm::vec3& p) { m_position = p; UpdateMatrix(); }

		const glm::mat4& GetMatrix() const
		{
			return m_matrix;
		}

	private:

		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
		glm::mat4 m_matrix;
		void UpdateMatrix()
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(m_rotation));
			m_matrix = glm::translate(glm::mat4(1.0), m_position) * rotation * glm::scale(glm::mat4(1.0), m_scale);
		}
	};
}