#include <V5/Scene/Scene.h>
#include <V5/Scene/Entity.h>
#include <V5/Components/Components.h>
#include <V5/Core/Logger.h>
#include "../Renderer/Renderer.h"
#include "../Renderer/Renderer2D.h"

using namespace V5Core;
using namespace V5Rendering;

Entity Scene::CreateEntity()
{
	Entity e(m_enttRegistry.create(), this);
	e.AddComponent<Transform>();
	return e;
}

void Scene::UpdateEditor(double dt)
{

}

void Scene::UpdateRuntime(double dt)
{

}

void Scene::RenderEditor(V5Rendering::EditorCamera& camera)
{
	Renderer::Instance().GetRenderer2D().Begin(camera.GetViewProjectionMatrix());

	auto entities = m_enttRegistry.view<Transform>();

	for (const auto& e : entities)
	{
		Transform& t = entities.get<Transform>(e);
		Renderer::Instance().GetRenderer2D().DrawQuad(t, { 1,1,1,1 },  nullptr);
	}
	
	Renderer::Instance().GetRenderer2D().End();

}