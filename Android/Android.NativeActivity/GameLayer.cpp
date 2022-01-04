#pragma once
#include "GameLayer.h"



void GameLayer::OnUpdate(double dt)
{
	int a = 0;

	m_activeScene.UpdateRuntime(dt);

}
void GameLayer::OnRender() {}
void GameLayer::OnAttach() {}
void GameLayer::OnImGuiRender() {}
void GameLayer::OnEvent(V5Core::Event& e) {}