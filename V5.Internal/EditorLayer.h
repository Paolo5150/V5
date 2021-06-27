#pragma once

#include <V5/Core/Layer.h>
#include <V5/Core/Logger.h>
#include <V5/Event/Event.h>
#include <V5/Core/Input.h>
#include <V5/Event/InputEvents.h>
#include <tuple>


class EditorLayer : public V5Core::Layer
{
public:
	EditorLayer() : Layer("EditorLayer"){};

	void OnUpdate() override;
	void OnAttach() override;

	void OnEvent(V5Core::Event& e) override;

};