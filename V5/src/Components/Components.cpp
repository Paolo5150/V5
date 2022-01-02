#pragma once
#include <V5/Components/Components.h>
#include <V5/Core/Logger.h>


using namespace V5Core;

Transform::Transform(bool ignoreRotation) :
	m_ignoreRotation(ignoreRotation)
{
	m_scale = glm::vec3(1, 1, 1);
	SetRotation({ 0,0,0 });
	UpdateMatrix();
}

void Transform::SetPosition(const glm::vec3& p, bool updateMatrix)
{
	m_position = p;
}

void Transform::SetScale(const glm::vec3& s, bool updateMatrix)
{
	m_scale = s;
}
/* Rotation matrix updated only when needed, as it is expensive*/
void Transform::SetRotation(const glm::vec3& r, bool updateMatrix)
{
	if (!m_ignoreRotation)
	{
		m_rotation = r;
		m_rotationMatrix = glm::eulerAngleYXZ(glm::radians(m_rotation.x), glm::radians(m_rotation.y), glm::radians(m_rotation.z));
	}
}

const glm::vec3& Transform::GetPosition() { return m_position; }
const glm::vec3& Transform::GetScale() { return m_scale; }
const glm::vec3& Transform::GetRotation() { return m_rotation; }

void Transform::UpdateMatrix()
{
	if(m_ignoreRotation)
		m_matrix = glm::translate(glm::mat4(1.0), m_position) * glm::scale(glm::mat4(1.0), m_scale);
	else
		m_matrix = glm::translate(glm::mat4(1.0), m_position) * m_rotationMatrix * glm::scale(glm::mat4(1.0), m_scale);

}

const glm::mat4& Transform::GetMatrix() const
{
	return m_matrix;
}
