#pragma once

#include "Definitions.h"

class TSOP
{
public:
	TSOP(uint8_t pin)
		: m_Pin(pin)
	{ }

	void Update()
	{
		int value = analogRead(m_Pin);
		if (value < IR_BACKGROUND)
			m_Value = 1;
		else
			m_Value = 0;
	}

	uint8_t GetValue() const { return m_Value; }
private:
	uint8_t m_Pin = 0;
	uint8_t m_Value = 0;
};