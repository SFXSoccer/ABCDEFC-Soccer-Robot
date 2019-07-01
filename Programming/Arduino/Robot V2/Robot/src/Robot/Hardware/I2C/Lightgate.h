#pragma once

#include "I2CDevice.h"

class Lightgate : public I2CDevice
{
public:
	Lightgate() : I2CDevice()
	{}

	Lightgate(const char* name, const uint8_t address)
		: I2CDevice(name, address)
	{}

	void Update() override
	{
		delayMicroseconds(25);
		if (m_ReadTimer >= SENSOR_I2C_DELAY_MS)
		{
			Wire.requestFrom((int)m_Address, 1);

			int count = 0;
			while (Wire.available() != 0)
			{
				m_CapturedBall = Wire.read() != 0x00;
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

	void SetActive(bool active)
	{
		Wire.beginTransmission(m_Address);
		Wire.write(CMD_LIGHTGATE);
		Wire.write(active ? 0x01 : 0x00);
		Wire.endTransmission();
	}

	bool GetValue() const { return m_CapturedBall; }
	operator bool() const { return m_CapturedBall; }
private:
	bool m_CapturedBall = false;
	Timer m_ReadTimer;
};