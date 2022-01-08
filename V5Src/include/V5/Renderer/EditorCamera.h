#pragma once
#include "Camera.h"
#include <glm/gtx/quaternion.hpp>
#include <V5/Event/InputEvents.h>

namespace V5Rendering
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera(float fov, float aspect, float n, float f);
		const glm::mat4& GetViewMatrix() { return m_viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_viewProjectionMatrix; }
		void UpdateViewMatrix();
		glm::vec3 GetForward();
		glm::vec3 GetUp();
		glm::vec3 GetRight();
		glm::quat GetRotationQuat();

		void OnUpdate(double dt);
		void OnEvent(V5Core::Event& e) ;


	private:
		float m_fov;
		float m_aspect;
		float m_near;
		float m_far;
		
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;
		glm::vec3 m_position;
		float m_yaw;
		float m_pitch;

		glm::vec2 m_prevMousePosition;

	};
}
