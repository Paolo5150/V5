#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <V5/Renderer/Texture.h>
#include <set>
#include <V5/Scene/Entity.h>


namespace V5Core
{
	class Component
	{
	public:
		Entity* entity;
		virtual void OnComponentAttached(Entity* e) { entity = e; }
		bool Active = true;
	};

	class Transform : public Component
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

		void UpdateMatrix();
		void SetParent(Transform& transform);

		const glm::mat4& GetMatrix() const;

	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
		glm::mat4 m_matrix;
		glm::mat4 m_rotationMatrix;
		bool m_ignoreRotation = false;
		Transform* m_parent = nullptr;
		std::set<Transform*> m_children;
		
	};

	/*
		Sprite renderer and tile renderer are basically identical, but they are used by 2 different renderers (Renderer2D and TileRenderer2D)
		Tiles ignore rotation entirely, making them more performant
	*/
	class SpriteRenderer : public Component
	{
	public:
		V5Rendering::Texture2D* Texture;
		glm::vec4 Color = { 1,1,1,1 };

		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(V5Rendering::Texture2D * tex = nullptr, const glm::vec4 & color = { 1,1,1,1 })
			: Texture(tex), Color(color) {}
	};

	class TileRenderer : public Component
	{
	public:
		V5Rendering::Texture2D* Texture;
		glm::vec4 Color = { 1,1,1,1 };
		void OnComponentAttached(Entity* e) { 
			Component::OnComponentAttached(e);
			e->GetComponent<Transform>().SetIgnoreRotation(true);
		}

		TileRenderer() = default;
		TileRenderer(const TileRenderer&) = default;
		TileRenderer(V5Rendering::Texture2D* tex = nullptr, const glm::vec4& color = { 1,1,1,1 })
			: Texture(tex), Color(color) {}

		
	};
}