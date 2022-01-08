#include <V5/Scene/TestScene.h>
#include <V5/Renderer/RenderCommand.h>
#include <V5/Core/Factory.h>
#include <V5/Core/ICore.h>
#include <V5/Event/WindowEvents.h>
#include <V5/Renderer/IRenderer2D.h>
#include <V5/Renderer/IRenderer.h>
#include <V5/Core/Logger.h>
#include <V5/Core/IWindow.h>
#include <V5/Renderer/Texture.h>
#include <V5/Debugging/Intrumentor.h>
#include <V5/Components/Components.h>
#include <V5/Utils/Random.h>
#include <V5/Core/AssetManager.h>
#include "V5/Scene/Entity.h"

using namespace V5Core;
using namespace V5Rendering;

namespace
{
	constexpr int QUAD_COUNT = 5000;
	std::unique_ptr<Texture2D> tt;
	std::unique_ptr<Texture2D> tt2;
	std::vector<Entity> entities;
	Entity par;
}

TestScene::TestScene()
{
	auto td = AssetManager::Instance().LoadTextureData("Textures/smiley.png", true);
	auto td2 = AssetManager::Instance().LoadTextureData("Textures/wall.jpg", true);
	tt = Texture2D::Create(td);
	tt2 = Texture2D::Create(td2);

	for (int i = 0; i < QUAD_COUNT; i++)
	{
		auto e = CreateEntity();
		e.GetComponent<Transform>().SetPosition({ i * 2, 0, 0 });
		e.GetComponent<Transform>().SetRotation({ 0,0,90 });
		e.AddComponent<TileRenderer>(tt2.get());

		e.GetComponent<Transform>().UpdateMatrix();
	}

	class TestScript : public Behavior
	{
		void Start() 
		{
		}
		void Update(double dt) 
		{
			auto& t = entity->GetComponent<Transform>();
			t.SetPosition(t.GetPosition() + glm::vec3(0.2f, 0, 1) * 1.0f * (float)dt);

		}
		void Destroy() 
		{

		}
	};
	// Try cube
	par = CreateEntity();
	par.AddComponent<TileRenderer>(tt.get());
	par.AddComponent<NativeScript>().Bind<TestScript>();

	auto e = CreateEntity();
	e.GetComponent<Transform>().SetPosition({ 0,0,0.5 });
	e.AddComponent<SpriteRenderer>(tt2.get());
	e.GetComponent<Transform>().UpdateMatrix();
	e.GetComponent<Transform>().SetParent(par.GetComponent<Transform>());

	auto e2 = CreateEntity();
	e2.GetComponent<Transform>().SetPosition({ 0,0.5,0 });
	e2.GetComponent<Transform>().SetRotation({ -90,0,0 });
	e2.AddComponent<SpriteRenderer>(tt2.get());
	e2.GetComponent<Transform>().UpdateMatrix();

	auto e3 = CreateEntity();
	e3.GetComponent<Transform>().SetPosition({ 0,-0.5,0 });
	e3.GetComponent<Transform>().SetRotation({ 90,0,0 });
	e3.AddComponent<SpriteRenderer>(tt2.get());
	e3.GetComponent<Transform>().UpdateMatrix();

	auto e4 = CreateEntity();
	e4.GetComponent<Transform>().SetPosition({ 0,0,-0.5 });
	e4.GetComponent<Transform>().SetRotation({ 0,180,0 });
	e4.AddComponent<SpriteRenderer>(tt2.get());
	e4.GetComponent<Transform>().UpdateMatrix();

	auto e5 = CreateEntity();
	e5.GetComponent<Transform>().SetPosition({ 0.5,0,0 });
	e5.GetComponent<Transform>().SetRotation({ 0,90,0 });
	e5.AddComponent<SpriteRenderer>(tt2.get());
	e5.GetComponent<Transform>().UpdateMatrix();

	auto e6 = CreateEntity();
	e6.GetComponent<Transform>().SetPosition({ -0.5,0,0 });
	e6.GetComponent<Transform>().SetRotation({ 0,-90,0 });
	e6.AddComponent<SpriteRenderer>(tt2.get());
	e6.GetComponent<Transform>().UpdateMatrix();
}
TestScene::~TestScene()
{

}