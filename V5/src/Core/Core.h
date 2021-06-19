#pragma once
#include <iostream>
#include <Core/IWindowListener.h>
#include <Core/ICore.h>

namespace V5Core
{
	class Window;
	class Application;

	class Core : public IWindowListener, public ICore
	{

	public:
		static Core& Instance();
		Core();
		~Core();

		void Start(Application* app, int winWidth, int winHeight, std::string wintitle) override;



	private:

		static std::unique_ptr<Core> s_Instance;
		bool m_isEngineRunning = false;
		std::unique_ptr<Application> m_Application;


		void Run();
		void Shutdown();
		void OnWindowOpen(Window& win) override;
		void OnWindowCloseRequested(Window& window) override;
		void OnWindowResized(Window& window, int w, int h) override;
		void OnFocusChanged(Window& window, int f) override;


	};
}
