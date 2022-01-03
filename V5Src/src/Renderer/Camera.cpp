#include <V5/Renderer/Camera.h>

using namespace V5Rendering;


Camera::Camera(float fov, float aspect, float nearP, float farP)
{
	m_projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearP, farP);
	m_projectionType = CameraProjectionType::PERSPECTIVE;

}
Camera::Camera(float left, float right, float bottom, float top, float nearP, float farP)
{
	m_projectionMatrix = glm::ortho(left, right, bottom, top, nearP, farP);
	m_projectionType = CameraProjectionType::ORTHOGRAPHIC;
}

void Camera::UpdateProjectionMatrix(float fov, float aspect, float nearP, float farP)
{
	m_projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearP, farP);
	m_projectionType = CameraProjectionType::PERSPECTIVE;
}
void Camera::UpdateProjectionMatrix(float left, float right, float bottom, float top, float nearP, float farP)
{
	m_projectionMatrix = glm::ortho(left, right, bottom, top, nearP, farP);
	m_projectionType = CameraProjectionType::ORTHOGRAPHIC;
}