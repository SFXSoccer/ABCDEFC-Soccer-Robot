#pragma once

#include "AnalogDevice.h"

namespace Robot {

	class AnalogLED : public AnalogDevice
	{
	public:
		AnalogLED() : AnalogDevice()
		{ }

		AnalogLED(const char* name, const uint8_t pin) 
			: AnalogDevice(name, pin)
		{ }
		
		int Read() override
		{
			Error::Report(Error::WARNING, "Cannot read an analog value with this device", m_Name, m_ID);
		}

		bool IsOn() { return m_Value > 0; }

		void operator=(uint8_t brightness) { Write(brightness); }
		operator int() const { return m_Value; }
	};

}