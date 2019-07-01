#pragma once

#include "../Device.h"

namespace Robot {

	class AnalogDevice : public Device
	{
	public:
		AnalogDevice()
			: Device(""), m_Pin(0), m_Mode(DEFAULT), m_Value(0)
		{ }

		AnalogDevice(const char* name, const uint8_t pin)
			: Device(name), m_Pin(pin), m_Mode(DEFAULT), m_Value(0)
		{ }

		virtual int Read() { return m_Value = analogRead(m_Pin); }
		virtual void Write(uint8_t value) { analogWrite(m_Pin, m_Value = value); }
		virtual void Reference(uint8_t mode) { analogReference(m_Mode = mode); }

		uint8_t GetPin() const { return m_Pin; }
		uint8_t GetMode() const { return m_Mode; }
		int GetValue() const { return m_Value; }
	protected:
		const uint8_t m_Pin;
		uint8_t m_Mode;
		int m_Value;
	};

}