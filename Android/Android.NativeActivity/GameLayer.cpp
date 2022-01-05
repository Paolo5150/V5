#pragma once
#include "GameLayer.h"
#include <V5/Renderer/RenderCommand.h>


void GameLayer::OnUpdate(double dt)
{
	int a = 0;

	m_activeScene.UpdateRuntime(dt);

}
void GameLayer::OnRender() {}

void GameLayer::OnAttach() 
{
	V5Rendering::RenderCommand::SetClearColor(1, 0, 0, 1);
}
void GameLayer::OnImGuiRender() {}
void GameLayer::OnEvent(V5Core::Event& e) {}