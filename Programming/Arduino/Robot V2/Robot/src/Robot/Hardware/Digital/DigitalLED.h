#pragma once

#include "DigitalDevice.h"

class DigitalLED : public DigitalDevice
{
public:
	DigitalLED() : DigitalDevice()
	{}

	DigitalLED(const char* name, uint8_t pin)
		: DigitalDevice(name, pin, OUTPUT)
	{}

	int Read() override
	{
		Error::Report(Error::WARNING, "Cannot read a digital value with this device", m_Name, m_ID);
		return 0;
	}

	void SetMode(uint8_t mode) override
	{
		Error::Report(Error::WARNING, "Cannot change pin mode with this device", m_Name, m_ID);
	}

	bool IsOn() const { return m_Value == HIGH; }

	void operator=(bool on) { Write(on ? HIGH : LOW); }
	operator bool() const { return m_Value; }
};