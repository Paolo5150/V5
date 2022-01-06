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

using namespace V5Rendering;
using namespace V5Core;

namespace
{
	std::unique_ptr<Camera> testCamera;
	glm::mat4 viewMat;
}

void GameLayer::OnAttach()
{
	V5Rendering::RenderCommand::SetClearColor(0.2f,0.2f,0.2f, 1);
	float ratio = (float)Factory::GetWindow().GetWidth() / Factory::GetWindow().GetHeight();
	testCamera = std::make_unique<Camera>(75, ratio, 0.1f, 1000.0f);
	viewMat = glm::lookAt(glm::vec3(1,0,5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	for (int i = 0; i < 2; i++)
	{
		auto e = m_activeScene.CreateEntity();
		e.GetComponent<Transform>().SetPosition({ i * 2, 0, 0 });
		e.AddComponent<TileRenderer>(nullptr, glm::vec4(1,1,1,1));

		e.GetComponent<Transform>().UpdateMatrix();
	}

}

void GameLayer::OnUpdate(double dt)
{
	m_activeScene.UpdateRuntime(dt);


}
void GameLayer::OnRender() 
{
	m_activeScene.RenderRuntime(testCamera->GetProjectionMatrix() * viewMat);
	//V5Core::Factory().GetRenderer().DrawSample();
}


void GameLayer::OnImGuiRender() {}
void GameLayer::OnEvent(V5Core::Event& e) {}