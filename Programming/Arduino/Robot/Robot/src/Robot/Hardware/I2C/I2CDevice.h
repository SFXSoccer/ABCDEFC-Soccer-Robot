#pragma once

#include "../Device.h"

namespace Robot {

	class I2CDevice : public Device
	{
	public:
		I2CDevice() 
			: Device(""), m_Address(0x00)
		{
			Wire.begin();
		}

		I2CDevice(const char* name, const uint8_t address)
			: Device(name), m_Address(address)
		{
			Wire.begin();
		}

		virtual void Init() { }
		virtual void Update() = 0;

		bool Check()
		{
			Wire.beginTransmission(m_Address);
			if (Wire.endTransmission() == 0)
				return true;
			else
				return false;
		}

		uint8_t GetAddress() const { return m_Address; }
	protected:
		const uint8_t m_Address;
	};

}