#pragma once

#include "DigitalDevice.h"

namespace Robot {

	class Button : public DigitalDevice
	{
	public:
		Button() : DigitalDevice()
		{ }

		Button(const const char* name, uint8_t pin)
			: DigitalDevice(name, pin, INPUT)
		{ }

		void Write(uint8_t value) override
		{
			Error::Report(Error::WARNING, "Cannot write a digital value to this device", m_Name, m_ID);
		}

		void SetMode(uint8_t mode) override
		{
			Error::Report(Error::WARNING, "Cannot change pin mode with this device", m_Name, m_ID);
		}

		bool IsPressed() const { return m_Value; }

		operator bool() const { return m_Value; }
	};

}