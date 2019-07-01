#pragma once

#include "../Device.h"

namespace Robot {

	class DigitalDevice : public Device
	{
	public:
		DigitalDevice()
			: Device(""), m_Pin(0), m_Mode(OUTPUT), m_Value(LOW)
		{
			pinMode(m_Pin, m_Mode);
		}

		DigitalDevice(const char* name, const uint8_t pin, uint8_t mode = OUTPUT)
			: Device(name), m_Pin(pin), m_Mode(mode), m_Value(LOW)
		{
			pinMode(m_Pin, m_Mode);
		}
		
		virtual int Read() { return m_Value = digitalRead(m_Pin); }
		virtual void Write(uint8_t value) { digitalWrite(m_Pin, m_Value = value); }

		virtual void SetMode(uint8_t mode) { pinMode(m_Pin, m_Mode = mode); }

		uint8_t GetPin() const { return m_Pin; }
		uint8_t GetMode() const { return m_Mode; }
		uint8_t GetValue() const { return m_Value; }
	protected:
		const uint8_t m_Pin;
		uint8_t m_Mode;
		uint8_t m_Value;
	};

}