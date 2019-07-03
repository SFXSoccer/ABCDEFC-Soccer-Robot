#pragma once

#include <Robot/Hardware/Device.h>

class Koala : public Device
{
public:
	Koala() : Device() 
	{ }

	Koala(const char* name, uint8_t fadePin, uint8_t blinkPin)
		: Device(name), m_FadePin(fadePin), m_BlinkPin(blinkPin)
	{
		pinMode(fadePin, OUTPUT);
		pinMode(blinkPin, OUTPUT);

		digitalWrite(blinkPin, HIGH);
		digitalWrite(fadePin, HIGH);
	}

	void Update()
	{
		if (m_PrevFlicker >= m_NextBlink)
		{
			if (m_PrevFlicker <= m_NextBlink + 50)
				digitalWrite(m_BlinkPin, LOW);
			else if (m_PrevFlicker <= m_NextBlink + 100)
				digitalWrite(m_BlinkPin, HIGH);
			else if (m_PrevFlicker <= m_NextBlink + 150)
				digitalWrite(m_BlinkPin, LOW);
			else if (m_PrevFlicker <= m_NextBlink + 200)
				digitalWrite(m_BlinkPin, HIGH);
			else if (m_PrevFlicker <= m_NextBlink + 250)
				digitalWrite(m_BlinkPin, LOW);
			else if (m_PrevFlicker <= m_NextBlink + 300)
				digitalWrite(m_BlinkPin, HIGH);
			else
			{
				m_PrevFlicker.Restart();
				m_NextBlink = random(1000, 5000);
			}
		}

		if (m_FadeTimer > 2)
		{
			m_Fade += (m_FlipFade ? -1 : 1);
			if (m_Fade == 255 || m_Fade == 0)
				m_FlipFade = !m_FlipFade;

			analogWrite(m_FadePin, m_Fade);
			m_FadeTimer.Restart();
		}
	}

private:
	Timer m_PrevFlicker;
	Timer m_FadeTimer;

	uint8_t m_FadePin;
	uint8_t m_BlinkPin;

	uint16_t m_NextBlink = 1000;

	uint8_t m_Fade = 0;
	bool m_FlipFade = false;
};