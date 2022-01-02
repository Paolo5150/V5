#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace V5Rendering
{
	enum class CameraProjectionType
	{
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	class Camera
	{
	public:
		Camera(float fov, float aspect, float near, float far);
		Camera(float left, float right, float bottom, float top, float near, float far);

		const glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
		void UpdateProjectionMatrix(float fov, float aspect, float near, float far);
		void UpdateProjectionMatrix(float left, float right, float bottom, float top, float near, float far);

	protected:
		glm::mat4 m_projectionMatrix;
		CameraProjectionType m_projectionType;
	};
}
