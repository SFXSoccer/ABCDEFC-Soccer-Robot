#pragma once

#include "Definitions.h"

class LightSensor
{
public:
	LightSensor(uint8_t pin)
		: m_Pin(pin)
	{
		Calibrate();
	}

	void Update()
	{
		int value = analogRead(m_Pin);
		if (value > m_DefaultValue + LIGHT_COLOR_WHITE_BUFFER)
			m_Value = 1;
		else
			m_Value = 0;
	}

	void Calibrate()
	{
		for (int i = 0; i < CALIBRATION_COUNT; i++)
			m_DefaultValue += analogRead(m_Pin);
		m_DefaultValue = round(m_DefaultValue / CALIBRATION_COUNT);
	}

	uint8_t GetValue() const { return m_Value; }
private:
	uint8_t m_Pin = 0;
	uint8_t m_Value = 0;
	uint16_t m_DefaultValue = 0;
};