#pragma once

#include <string>
#include <V5/Core/LayerStack.h>
#include "ImGuiLayer.h"

namespace V5Core
{
	class Event;
	class Layer;
	class Scene;

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
		std::unique_ptr<Scene> m_activeScene;
	
	private:

		void Update(double dt);
		void Render();
		void OnQuit(); //Called by Core, no need to handle the WindowCloseEvent in this class
		void OnEvent(Event& e);
		LayerStack m_layerStack;
		std::string m_name;

		//Special layer
		ImGuiLayer* m_imGuiLayer; //Use pointers as they are deleted in Appliocaiton on quit, when layers are cleared

	};
}
