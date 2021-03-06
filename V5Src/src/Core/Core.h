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

		void Start(Application* app, int winWidth, int winHeight, std::string wintitle, void* windowCallback = nullptr) override;
		IWindow& GetWindow() override { return *m_window; };
		void TriggerEvent(Event& event) override;


	private:

		static std::unique_ptr<Core> s_Instance;

		bool m_isEngineRunning = false;
		Application* m_Application;
		std::unique_ptr<IWindow> m_window;

		void OnEvent(Event& e);
		void Run();
		void Shutdown();

		double m_prevTime;
		double m_deltaTime;
		double m_looseDeltaTime;
		double m_accumulator = 0;

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
