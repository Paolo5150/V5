#pragma once

#include <V5/Core/Layer.h>
#include <V5/Core/Logger.h>
#include <V5/Event/Event.h>
#include <V5/Core/Input.h>
#include <V5/Event/InputEvents.h>
#include <V5/Renderer/EditorCamera.h>
#include <V5/Scene/Scene.h>

#include <tuple>


class EditorLayer : public V5Core::Layer
{
public:
	enum EditorState
	{
		EDIT,
		PLAY
	};

	EditorLayer() : Layer("EditorLayer"){};

	void OnUpdate(double dt) override;
	void OnRender() override;
	void OnAttach(V5Core::Scene* scene) override;
	void OnImGuiRender() override;

	void OnEvent(V5Core::Event& e) override;

private:
	void ToggleState();
	float m_frameTime;
	std::unique_ptr<V5Rendering::EditorCamera> m_editorCamera;
	EditorState m_editorState = EditorState::EDIT;
};