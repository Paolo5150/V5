#pragma once
#include <chrono>
#include <iostream>
#include <V5/Core/ITime.h>
#include <functional>
#include <vector>

namespace V5Core
{
	class Time 
	{
	public:
		friend class Core;

		static void StartTimer();

		/**
		* Returns the difference beteen now and the last StartTimer called, in seconds
		*/
		static double StopTimer();

		/**
		* Returns the difference beteen now and the last StartTimer called, in nanoseconds
		*/
		static double Now();

		static float GetDeltaTime() { return DeltaTime; }

	private:
		static float DeltaTime; // Set by Core, in Update
		static std::chrono::high_resolution_clock::time_point m_timeStart;
	};
}