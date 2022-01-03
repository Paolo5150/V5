#pragma once
#include "entt.hpp"
#include <V5/Renderer/EditorCamera.h>

namespace V5Core
{
	class Entity;

	class Scene
	{
	public:
		friend class Entity;
		Scene() = default;
		Entity CreateEntity();

		void UpdateEditor(double dt);
		void UpdateRuntime(double dt);

		void RenderEditor(V5Rendering::EditorCamera& camera);

	private:
		entt::registry m_enttRegistry;
	};

}
