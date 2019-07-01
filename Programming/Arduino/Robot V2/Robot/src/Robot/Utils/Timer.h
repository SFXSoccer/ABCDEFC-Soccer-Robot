#pragma once

#include "../Core.h"

class Timer
{
public:
	Timer()
	{
		Restart();
	}

	void Start()
	{
		m_Stop = -1;
	}

	void Stop()
	{
		if (m_Stop == -1)
			m_Stop = millis();
	}

	void Reset()
	{
		m_Stop = m_Start = millis();
	}

	void Restart()
	{
		m_Start = millis();
		Start();
	}

	long Elapsed() const { return m_Stop == -1 ? millis() - m_Start : m_Stop - m_Start; }
	double Seconds() const { return (double)Elapsed() / 1000; }

	operator long() const { return Elapsed(); }
private:
	long m_Start = 0;
	long m_Stop = -1;
	long m_Offset = 0;
};