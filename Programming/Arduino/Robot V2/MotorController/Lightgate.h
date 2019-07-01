#pragma once

#include "Definitions.h"
#include "Timer.h"

class Lightgate
{
public:
	Lightgate(uint8_t power, uint8_t read)
		: m_PinPower(power), m_PinRead(read)
	{
		pinMode(m_PinPower, OUTPUT);
		Toggle();
	}

	void Update()
	{
		if (m_ReadDelay > ((m_Delay == 0) ? DELAY_LIGHTGATE : DELAY_BALL_DETECTED))
		{
			m_Value = analogRead(m_PinRead);
			if (m_Value > m_HighRead) m_HighRead = m_Value;

			if (m_Value < (m_HighRead * m_Sensitivity))
			{
				m_CapturedBall = true;
				m_Delay = DELAY_BALL_DETECTED;
			}
			else if (m_Value > (m_HighRead * m_Sensitivity))
			{
				m_CapturedBall = false;
				m_Delay = DELAY_LIGHTGATE;
			}
			m_ReadDelay.Restart();
		}
	}

	void Toggle()
	{
		m_HighRead = 0;
		m_Active = !m_Active;
		digitalWrite(m_PinPower, m_Active ? HIGH : LOW);
	}

	void SetSensitivity(float value)
	{
		value = value < 0 ? 0 : value > 1 ? 1 : value;
		m_Sensitivity = value;
	}

	uint16_t GetReading() const { return m_Value; }
	uint16_t GetHighReading() const { return m_HighRead; }
	bool Active() const { return m_Active; }
	bool CapturedBall() const { return m_CapturedBall; }

	operator int() const { return m_Value; }
private:
	uint16_t m_Value = 0;
	uint16_t m_HighRead = -1;

	uint8_t m_PinPower = 0;
	uint8_t m_PinRead = 0;

	uint32_t m_Delay = 0;

	float m_Sensitivity = 0.2;
	bool m_CapturedBall = false;
	bool m_Active = false;

	Timer m_ReadDelay;
};