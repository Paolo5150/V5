#pragma once
#include "entt.hpp"

namespace V5Core
{
	class Entity;

	class Scene
	{
	public:
		friend class Entity;
		Scene() = default;
		Entity CreateEntity();

	private:
		entt::registry m_enttRegistry;
	};

}
