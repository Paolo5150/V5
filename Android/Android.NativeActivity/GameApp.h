#pragma once
#include <V5/Application/Application.h>
#include <V5/Event/Event.h>


class GameApp : public V5Core::Application
{
public:
	GameApp() : Application("GameApp") {};
	void OnStart() override;
	~GameApp() {};
};