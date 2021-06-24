#include "Time.h"

using namespace V5Core;

std::unique_ptr<Time> Time::s_instance;

namespace
{
	int FPS = 60;
	double frameTime = 1.0 / FPS;
}

Time& Time::Instance()
{
	if (s_instance == nullptr)
	{
		s_instance = std::make_unique<Time>();
	}

	return *s_instance;
}

void Time::Init()
{
	m_prevTime = glfwGetTime();
}


double Time::GetDeltaTimeSeconds()
{
	return m_deltaTime;
}

double Time::GetLooseDeltaTimeSeconds()
{
	return m_looseDeltaTime;
}


void Time::Update()
{
	double now = glfwGetTime();
	m_looseDeltaTime = now - m_prevTime;
	m_prevTime = now;

	auto delta = m_looseDeltaTime;
	m_accumulator += delta;

	while (m_accumulator > frameTime)
	{
		for (auto c : m_updateCallbacks)
			c(m_accumulator);

		m_deltaTime = m_accumulator;
		//Update callback
		m_accumulator -= frameTime;
	}

	//Render callback
	for (auto c : m_renderCallbacks)
		c();
}


