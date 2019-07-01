#pragma once

#include "DigitalDevice.h"

class Button : public DigitalDevice
{
public:
	Button() : DigitalDevice()
	{}

	Button(const char* name, uint8_t pin)
		: DigitalDevice(name, pin, INPUT)
	{}

	int Read() override
	{
		m_Value = digitalRead(m_Pin);

		if (m_PreviousValue != m_Value && m_Value == true)
		{
			digitalWrite(13, m_Value);
			m_PressedEvent();
		}

		return m_PreviousValue = m_Value;
	}

	void Write(uint8_t value) override
	{
		Error::Report(Error::WARNING, "Cannot write a digital value to this device", m_Name, m_ID);
	}

	void SetMode(uint8_t mode) override
	{
		Error::Report(Error::WARNING, "Cannot change pin mode with this device", m_Name, m_ID);
	}

	void SetPressedEvent(void (*function)())
	{
		m_PressedEvent = function;
	}

	bool IsPressed() const { return m_Value; }

	operator bool() const { return m_Value; }
private:
	bool m_PreviousValue = false;
	void (*m_PressedEvent)();
};