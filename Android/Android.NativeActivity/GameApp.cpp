#include "GameApp.h"
#include "GameLayer.h"
#include <V5/Scene/TestScene.h>

void GameApp::OnStart()
{
	Application::OnStart();
	m_activeScene = std::make_unique<TestScene>();
	PushLayer(new GameLayer());
}
