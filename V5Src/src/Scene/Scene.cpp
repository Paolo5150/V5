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

void Scene::OnStart()
{
	V5CLOG_INFO("Scene start");

	

}
void Scene::OnEnd()
{
	V5CLOG_INFO("Scene end");
	auto view = m_enttRegistry.view<NativeScript>();

	view.each([](auto entity, auto& ns) {
		ns.Destroy(&ns);

		});

}

void Scene::UpdateEditor(double dt)
{

}

void Scene::UpdateRuntime(double dt)
{

	auto view = m_enttRegistry.view<NativeScript>();
	view.each([&](auto entity, auto& ns) {

		if (ns.Instance == nullptr)
		{
			ns.Instance = ns.Instantiate();
			ns.Instance->entity = ns.entity;
			ns.Instance->Start();
		}
		
		if (ns.Active)
		{
			ns.Instance->Update(dt);
		}

		});
}

void Scene::RenderRuntime(const glm::mat4& viewProjection)
{
	//TODO enable vulkan when ready
	if (Renderer::Instance().GetRenderAPI().GetAPI() == RendererAPI::API::Vulkan) return;
	
	{
		Renderer::Instance().GetTileRenderer2D().Begin(viewProjection);

		auto view = m_enttRegistry.view<Transform, TileRenderer>();

		view.each([](auto entity, auto& t, auto& rend) {
			if (rend.Active)
				Renderer::Instance().GetTileRenderer2D().DrawQuad(t.GetPosition(), t.GetScale(), rend.Color, rend.Texture);
			});
		Renderer::Instance().GetTileRenderer2D().End();
	}

	{
		Renderer::Instance().GetRenderer2D().Begin(viewProjection);

		auto view = m_enttRegistry.view<Transform, SpriteRenderer>();

		view.each([](auto entity, auto& t, auto& sr) {
			if (sr.Active)
				Renderer::Instance().GetRenderer2D().DrawQuad(t, sr.Color, sr.Texture);

			});

		Renderer::Instance().GetRenderer2D().End();
	}
}

void Scene::RenderRuntime(V5Rendering::Camera& camera)
{
	RenderRuntime(camera.GetProjectionMatrix());
}


void Scene::RenderEditor(V5Rendering::EditorCamera& camera)
{
	RenderRuntime(camera.GetViewProjectionMatrix());
}