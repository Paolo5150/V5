#include "GameApp.h"
#include "GameLayer.h"

void GameApp::OnStart()
{
	Application::OnStart();
	PushLayer(new GameLayer());
}
