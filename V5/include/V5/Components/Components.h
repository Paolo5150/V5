#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <V5/Renderer/Texture.h>


namespace V5Core
{
	class Transform
	{
	public:
		Transform()
		{
			m_scale = glm::vec3(1, 1, 1 );
			m_rotation = glm::vec3(0,0,0 );
			UpdateMatrix();
		}

		void SetPosition(const glm::vec3& p) { m_position = p; UpdateMatrix(); }
		void SetScale(const glm::vec3& s) { m_scale = s; UpdateMatrix(); }
		void SetRotation(const glm::vec3& r) { m_rotation = r; UpdateMatrix(); }

		const glm::vec3& GetPosition() { return m_position; }
		const glm::vec3& GetScale() { return m_scale; }
		const glm::vec3& GetRotation() { return m_rotation; }

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


	class SpriteRenderer
	{
		public:
			SpriteRenderer(std::shared_ptr<V5Rendering::Texture2D> texture = nullptr, const glm::vec4& color = { 1,1,1,1 }) :
				m_texture(texture),
				m_color(color)
			{
			}

			std::shared_ptr<V5Rendering::Texture2D> GetTexture() { return m_texture; }
			glm::vec4& GetColor() { return m_color; }
		private:
			std::shared_ptr<V5Rendering::Texture2D> m_texture;
			glm::vec4 m_color;
	};
}