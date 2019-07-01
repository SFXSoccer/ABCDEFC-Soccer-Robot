#pragma once

#include "../Core.h"

class EventTimer
{
public:
	EventTimer() {}

	EventTimer(uint32_t interval, bool usingMicros = false)
		: m_Interval(interval), m_UsingMicros(usingMicros)
	{
		if (micros)
			m_Start = micros();
		else
			m_Start = millis();
	}

	void Update()
	{
		if ((m_UsingMicros ? micros() : millis()) - m_Start >= m_Interval)
		{
			m_ElapsedFunc();
			m_Start = (m_UsingMicros ? micros() : millis());
		}
	}

	void SetElapsedEvent(void (*function)())
	{
		m_ElapsedFunc = function;
	}

	void SetInterval(uint32_t interval, bool usingMicros = false)
	{
		if (micros)
			m_Start = micros();
		else
			m_Start = millis();
	}

	bool UsingMicros() const { return m_UsingMicros; }
private:
	void (*m_ElapsedFunc)();
	uint32_t m_Start;
	uint32_t m_Interval;
	bool m_UsingMicros;
};