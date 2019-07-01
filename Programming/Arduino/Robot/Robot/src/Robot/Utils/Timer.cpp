#include "Timer.h"

namespace Robot {

	Timer::Timer()
	{
		Restart();
	}

	void Timer::Start()
	{
		m_Offset += millis() - m_Stop;
		m_Stop = -1;
	}

	void Timer::Stop()
	{
		if (m_Stop == -1)
			m_Stop = millis();
	}

	void Timer::Reset()
	{
		m_Offset += millis() - m_Stop;
		m_Stop = m_Start = millis();
	}

	void Timer::Restart()
	{
		m_Start = millis();
		Start();
	}

	long Timer::Elapsed() const
	{
		return m_Stop == -1 ? millis() - m_Start : m_Stop - m_Start;
	}

	long Timer::Millis() const
	{
		return Elapsed();
	}

	double Timer::Seconds() const
	{
		return (double)Elapsed() / 1000;
	}

}