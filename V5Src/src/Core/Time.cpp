#include <V5/Core/Time.h>

using namespace V5Core;

std::chrono::high_resolution_clock::time_point Time::m_timeStart;
 float Time::DeltaTime; // Set by Core, in Update


void Time::StartTimer()
{
	m_timeStart = std::chrono::high_resolution_clock::now();
}

 double Time::Now()
{
	 auto now = std::chrono::high_resolution_clock::now();
	 auto duration = now.time_since_epoch();
	 auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
	 return nano;
}


double Time::StopTimer()
{
	auto now = std::chrono::high_resolution_clock::now();

	//auto time_span = std::chrono::duration_cast<std::chrono::duration<double, std::chrono::milliseconds>>(now - m_timeStart);
	auto time_span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(now - m_timeStart);

	return time_span.count();
}




