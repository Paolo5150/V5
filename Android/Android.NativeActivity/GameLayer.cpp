#pragma once
#include "GameLayer.h"
#include <V5/Renderer/RenderCommand.h>
#include <V5/Core/AssetManager.h>
#include <V5/Scene/Scene.h>
#include <V5/Scene/Entity.h>
#include <V5/Renderer/Camera.h>
#include <V5/Components/Components.h>
#include <V5/Core/Factory.h>
#include <V5/Core/IWindow.h>
#include <V5/Renderer/IRenderer.h>
#include <V5/Core/AssetManager.h>

using namespace V5Rendering;
using namespace V5Core;

namespace
{
	std::unique_ptr<Camera> testCamera;
	glm::mat4 viewMat;
	std::unique_ptr<Texture2D> tt;
	std::unique_ptr<Texture2D> tt2;

}

void GameLayer::OnAttach()
{
	V5Rendering::RenderCommand::SetClearColor(0.2f,0.2f,0.2f, 1);
	float ratio = (float)Factory::GetWindow().GetWidth() / Factory::GetWindow().GetHeight();
	testCamera = std::make_unique<Camera>(75, ratio, 0.1f, 1000.0f);
	viewMat = glm::lookAt(glm::vec3(1,0,15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	auto td = AssetManager::Instance().LoadTextureData("Textures/smiley.png",true);
	auto td2 = AssetManager::Instance().LoadTextureData("Textures/wall.jpg",true);
	tt = Texture2D::Create(td);
	tt2 = Texture2D::Create(td2);

	for (int i = 0; i < 12; i++)
	{
		auto e = m_activeScene.CreateEntity();
		e.GetComponent<Transform>().SetPosition({ i * 2, 0, 0 });
		e.GetComponent<Transform>().UpdateMatrix();

		if(i % 2 == 0)
			e.AddComponent<TileRenderer>(tt.get());
		else
			e.AddComponent<TileRenderer>(tt2.get());
	}
}

void GameLayer::OnUpdate(double dt)
{
	m_activeScene.UpdateRuntime(dt);

	static float timer = 0;
	static float timer2 = 0;
	static int counter = 0;
	static double FPS = 0;
	timer += dt;
	timer2+= dt;
	FPS += 1.0 / dt;
	counter++;

	if (timer > 1.0f)
	{
		FPS /= counter;
		timer = 0;
		counter = 0;
	//	LOGI("FPS %f", FPS);
		FPS = 0;

	}
	viewMat = glm::lookAt(glm::vec3(timer2 * 2, 0, 15), glm::vec3(timer2 * 2, 0, 15) + glm::vec3(0,0,-1), glm::vec3(0, 1, 0));


}
void GameLayer::OnRender() 
{
	m_activeScene.RenderRuntime(testCamera->GetProjectionMatrix() * viewMat);
}


void GameLayer::OnImGuiRender() {}
void GameLayer::OnEvent(V5Core::Event& e) {}