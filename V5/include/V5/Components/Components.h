#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <V5/Renderer/Texture.h>
#include <V5/Scene/Entity.h>


namespace V5Core
{
	class Transform
	{
	public:
		Transform(bool ignoreRotation = false);

		void SetPosition(const glm::vec3& p, bool updateMatrix = false);
		void SetScale(const glm::vec3& s, bool updateMatrix = false);
		void SetRotation(const glm::vec3 & r, bool updateMatrix = false);
		void SetIgnoreRotation(bool ignore) { m_ignoreRotation = ignore; };

		const glm::vec3& GetPosition();
		const glm::vec3& GetScale();
		const glm::vec3& GetRotation();
		void OnComponentAttached(Entity* e) {}

		void UpdateMatrix();

		const glm::mat4& GetMatrix() const;

	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
		glm::mat4 m_matrix;
		glm::mat4 m_rotationMatrix;
		bool m_ignoreRotation = false;
		
	};

	/*
		Sprite renderer and tile renderer are basically identical, but they are used by 2 different renderers (Renderer2D and TileRenderer2D)
		Tiles ignore rotation entirely, making them more performant
	*/
	struct SpriteRenderer
	{
		V5Rendering::Texture2D* Texture;
		glm::vec4 Color = { 1,1,1,1 };
		void OnComponentAttached(Entity* e) {}

		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(V5Rendering::Texture2D * tex = nullptr, const glm::vec4 & color = { 1,1,1,1 })
			: Texture(tex), Color(color) {}
	};

	struct TileRenderer
	{
	public:
		V5Rendering::Texture2D* Texture;
		glm::vec4 Color = { 1,1,1,1 };
		void OnComponentAttached(Entity* e) { e->GetComponent<Transform>().SetIgnoreRotation(true); }

		TileRenderer() = default;
		TileRenderer(const TileRenderer&) = default;
		TileRenderer(V5Rendering::Texture2D* tex = nullptr, const glm::vec4& color = { 1,1,1,1 })
			: Texture(tex), Color(color) {}

		
	};
}