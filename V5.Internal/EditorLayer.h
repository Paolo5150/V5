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

	void OnUpdate() override
	{

	}

	void OnEvent(V5Core::Event& e) override
	{
		if (e.GetType() == V5Core::EventType::MouseBtnClick)
		{
			V5CLOG_INFO("EditorLayer received {0}", e.GetType());
		}
	}

};