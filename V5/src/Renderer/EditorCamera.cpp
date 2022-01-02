#include <V5/Renderer/EditorCamera.h>
#include <V5/Core/Input.h>
#include<V5/Core/KeyCodes.h>
#include <V5/Core/Logger.h>
using namespace V5Rendering;
using namespace V5Core;

namespace
{
	float MoveSpeed = 5.0f;
	float RotationSpeed = 40.0f;
}

EditorCamera::EditorCamera(float fov, float aspect, float n, float f) : Camera(fov, aspect, n, f),
m_fov(fov),
m_far(f),
m_near(n),
m_aspect(aspect),
m_pitch(0.0f),
m_yaw(0.0f)
{
	m_position = glm::vec3(0, 0, 2);
	UpdateViewMatrix();
	m_prevMousePosition = glm::vec2(Input::GetMousePosition()[0], Input::GetMousePosition()[1]);
}

void EditorCamera::UpdateViewMatrix()
{
	auto up = GetUp();
	m_viewMatrix = glm::lookAt(m_position, m_position + GetForward(), GetUp());

}

void EditorCamera::OnUpdate(double dt)
{
	glm::vec2 currentMouse(Input::GetMousePosition()[0], Input::GetMousePosition()[1]);
	auto delta = currentMouse - m_prevMousePosition;

	m_prevMousePosition = currentMouse;



	if (Input::IsMouseButtonHold(1))
	{
		if (Input::IsKeyHold(KeyCode::A))
		{
			m_position -= GetRight() * MoveSpeed * (float)dt;
		}
		else if (Input::IsKeyHold(KeyCode::D))
		{
			m_position += GetRight() * MoveSpeed * (float)dt;
		}
		else if (Input::IsKeyHold(KeyCode::W))
		{
			m_position += GetForward() * MoveSpeed * (float)dt;
		}
		else if (Input::IsKeyHold(KeyCode::S))
		{
			m_position -= GetForward() * MoveSpeed * (float)dt;
		}
		m_pitch -= delta.y * RotationSpeed * dt;
		m_yaw -= delta.x * RotationSpeed * dt;

		UpdateViewMatrix();
	}
}
void EditorCamera::OnEvent(V5Core::Event& e)
{

}

glm::quat EditorCamera::GetRotationQuat()
{
	return glm::quat(glm::vec3(glm::radians(m_pitch), glm::radians(m_yaw), 0.0f)); //No roll
}
glm::vec3 EditorCamera::GetForward()
{
	return GetRotationQuat() * glm::vec3(0, 0, -1);
}
glm::vec3 EditorCamera::GetUp()
{
	return GetRotationQuat() * glm::vec3(0, 1, 0);
}
glm::vec3 EditorCamera::GetRight()
{
	return GetRotationQuat() * glm::vec3(1, 0, 0);
}

