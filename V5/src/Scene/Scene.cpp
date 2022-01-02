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
	//Render tiles

	{
		Renderer::Instance().GetTileRenderer2D().Begin(camera.GetViewProjectionMatrix());

		auto view = m_enttRegistry.view<Transform, TileRenderer>();

		view.each([](auto entity, auto& t, auto& rend) {
			if(rend.Active)
				Renderer::Instance().GetTileRenderer2D().DrawQuad(t.GetPosition(), t.GetScale(), rend.Color, rend.Texture);
			});
		Renderer::Instance().GetTileRenderer2D().End();
	}
	
	{
		Renderer::Instance().GetRenderer2D().Begin(camera.GetViewProjectionMatrix());

		auto view = m_enttRegistry.view<Transform, SpriteRenderer>();

		view.each([](auto entity, auto& t, auto& sr) {
			if(sr.Active)
				Renderer::Instance().GetRenderer2D().DrawQuad(t, sr.Color, sr.Texture);

			});

		Renderer::Instance().GetRenderer2D().End();
	}

	

}