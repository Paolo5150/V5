#pragma once
#include "entt.hpp"
#include "Scene.h"

namespace V5Core
{
	class Scene;

	class Entity
	{
	public:
		friend class Scene;

		Entity() = default;
		Entity(entt::entity ent, Scene* scene);

		operator entt::entity() const { return m_enttHandle; }
		operator bool() const { return m_enttHandle != entt::null; }

		bool operator ==(const Entity& other) const { return m_enttHandle == other.m_enttHandle && m_scene == other.m_scene; }
		bool operator !=(const Entity& other) const { return !(*this == other); }

		template<typename T, typename... Args>
		T AddComponent(Args&&... args)
		{
			T& component = m_scene->m_enttRegistry.emplace<T>(m_enttHandle, std::forward<Args>(args)...);
			return component;
		}

		template <typename T>
		bool HasComponent()
		{
			return m_scene->m_enttRegistry.any_of<T>(m_enttHandle);
		}

	private:
		Scene* m_scene;
		entt::entity m_enttHandle;

	};
}
