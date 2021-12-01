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
		static void StartTimer();

		/**
		* Returns the difference betwwn now and the last StartTimer called
		*/
		static double StopTimer();

	private:


		static std::chrono::high_resolution_clock::time_point m_timeStart;
	};
}