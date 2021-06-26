#pragma once
#include <chrono>
#include <GLFW/glfw3.h>
#include <iostream>
#include <V5/Core/ITime.h>
#include <functional>
#include <vector>

namespace V5Core
{
	class Time : public ITime
	{
	public:
		static Time& Instance();

		double GetLooseDeltaTimeSeconds() override;
		double GetDeltaTimeSeconds() override;
		void Init();
		void Update();
		void Reset() { m_prevTime = glfwGetTime(); }
		void StartTimer();

		/**
		* Returns the difference betwwn now and the last StartTimer called
		*/
		double StopTimer();

		void RegisterUpdateCallback(std::function<void(double)> f) { m_updateCallbacks.push_back(f); };
		void RegisterRenderCallback(std::function<void()> f) { m_renderCallbacks.push_back(f); };

	private:
		static std::unique_ptr<Time> s_instance;
		double m_prevTime;
		double m_deltaTime;
		double m_looseDeltaTime;
		double m_accumulator = 0;

		std::vector <std::function<void(double)>> m_updateCallbacks;
		std::vector <std::function<void()>> m_renderCallbacks;
		std::chrono::high_resolution_clock::time_point m_timeStart;
	};
}