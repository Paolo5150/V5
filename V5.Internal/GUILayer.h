#pragma once

#include <V5/Core/Layer.h>
#include <V5/Core/Logger.h>
#include <V5/Event/Event.h>

class GUILayer : public V5Core::Layer
{
public:
	GUILayer() : Layer("GUILayer") {};

	void OnUpdate() override
	{
		//V5LOG_INFO("Update GUI layer");
	}


	void OnEvent(V5Core::Event& e) override
	{
		if (e.GetType() == V5Core::EventType::MouseBtnClick)
		{
			//V5CLOG_INFO("GUI layer received {0}", e.GetType());
			//e.Consume();
		}
		//

	}
};