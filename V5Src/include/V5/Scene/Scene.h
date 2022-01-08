#pragma once
#include "entt.hpp"
#include <V5/Renderer/EditorCamera.h>
#include <V5/Renderer/Camera.h>

namespace V5Core
{
	class Entity;

	class Scene
	{
	public:
		friend class Entity;
		Scene() = default;
		virtual ~Scene() = default;
		Entity CreateEntity();

		void OnStart();
		void OnEnd();
		void UpdateEditor(double dt);
		void UpdateRuntime(double dt);

		void RenderEditor(V5Rendering::EditorCamera& camera);
		void RenderRuntime(V5Rendering::Camera& camera);
		void RenderRuntime(const glm::mat4& viewProjection);

	private:
		entt::registry m_enttRegistry;
	};

}
