#pragma once

#include "../Dll.h"
#include <string>
#include <V5/Core/LayerStack.h>


namespace V5Core
{
	class Event;
	class Layer;

	class V5_API Application
	{
		friend class Core;

	public:
		Application(std::string name);
		virtual ~Application() {};

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	
	private:

		void OnStart();
		void Update();
		void OnQuit(); //Called by Core, no need to handle the WindowCloseEvent in this class
		void OnEvent(Event& e);
		LayerStack m_layerStack;
		std::string m_name;
	};
}
