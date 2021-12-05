#pragma once

#include <string>
#include <V5/Core/LayerStack.h>


namespace V5Core
{
	class Event;
	class Layer;

	class Application
	{
		friend class Core;

	public:
		Application(std::string name);
		virtual ~Application() {};

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	protected:
		/**
		* Called right before main loop starts, layers should be added here
		*/
		virtual void OnStart();

	
	private:

		void Update(double dt);
		void Render();
		void OnQuit(); //Called by Core, no need to handle the WindowCloseEvent in this class
		void OnEvent(Event& e);
		void UpdateImGuiLayers(); // Special update for imgui, needs to be called after clear screen 
		LayerStack m_layerStack;
		std::string m_name;
	};
}
