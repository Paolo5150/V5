#pragma once
#include <iostream>
#include <V5/Core/ICore.h>

namespace V5Core
{
	class IWindow;
	class Application;
	class Event;

	class Core :  public ICore
	{

	public:
		static Core& Instance();
		Core();
		~Core();

		void Start(Application* app, int winWidth, int winHeight, std::string wintitle) override;
		IWindow& GetWindow() override { return *m_window; };

	private:

		static std::unique_ptr<Core> s_Instance;

		bool m_isEngineRunning = false;
		Application* m_Application;
		std::unique_ptr<IWindow> m_window;

		void OnEvent(Event& e);
		void Run();
		void Shutdown();

		/**
		* Called By Time, this is the runtime update (follows FPS)
		*/
		void Update(double dt);

		/**
		* Called By Time
		*/
		void Render();

	};
}
