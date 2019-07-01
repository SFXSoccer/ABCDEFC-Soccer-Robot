#pragma once

#include "I2CDevice.h"

class TSOPSensorArray : public I2CDevice
{
public:
	TSOPSensorArray() : I2CDevice()
	{}

	TSOPSensorArray(const char* name, const uint8_t address)
		: I2CDevice(name, address)
	{}
	
	void Update() override
	{
		if (m_ReadTimer >= SENSOR_I2C_DELAY_MS)
		{
			Wire.requestFrom((int)m_Address, 16);

			int count = 0;
			while (Wire.available() != 0)
			{
				uint8_t high = Wire.read();
				uint8_t low = Wire.read();
				m_SensorValues[count] = (((high & 0xFF) << 8) | (low & 0xFF));
				count++;
			}

			if (count == 0)
				Error::Report(Error::CRITICAL, "Failed to get sensor data!!!", m_Name, m_ID);
			m_ReadTimer.Restart();
		}
	}

	bool VerifyConnection()
	{
		Timer timeout;
		Error::Report(Error::NONE, "Verifying connection...", m_Name, m_ID);
		bool result = false;
		while (!(result = Check()) && timeout < I2C_CONNECTION_TIMEOUT);

		if (timeout > I2C_CONNECTION_TIMEOUT || result == false)
		{
			Error::Report(Error::FAILURE, "Failed to connect (timeout)", m_Name, m_ID);
			return false;
		}
		Error::Report(Error::NONE, "Verifed connection", m_Name, m_ID);
		return true;
	}

	uint16_t GetValue(int sensor) const { return m_SensorValues[sensor]; }
	uint16_t operator[](int x) const { return m_SensorValues[x]; }
private:
	uint16_t m_SensorValues[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	Timer m_ReadTimer;
};