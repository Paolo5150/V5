#pragma once

#include <V5/Core/Layer.h>
#include <V5/Event/Event.h>
#include <V5/Scene/Scene.h>

#include <tuple>

class GameLayer : public V5Core::Layer
{
public:


	GameLayer() : Layer("GameLayer") {};

	void OnUpdate(double dt) override;
	void OnRender() override;
	void OnAttach() override;
	void OnImGuiRender() override;

	void OnEvent(V5Core::Event& e) override;

private:
	std::unique_ptr<V5Core::Scene> m_activeScene;
};