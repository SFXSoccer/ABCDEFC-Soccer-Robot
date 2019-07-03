#pragma once

#include "I2CDevice.h"

typedef struct MotorData
{
	int16_t Degree;
	int16_t Speed;
	int16_t Rotation;
	bool Rotate;
	uint8_t Pivot;

	MotorData() 
	{ }

	MotorData(int16_t degree, int16_t speed, int16_t rotation, bool rotate = false, uint8_t pivot = 0)
		: Rotate(rotate)
	{
		Degree = constrain(degree, -360, 360);
		Speed = constrain(speed, -255, 255);
		Rotation = constrain(rotation, -255, 255);
		Pivot = constrain(pivot, 0, 3);
	}

	bool Compare(MotorData data)
	{
		if (data.Degree == Degree && data.Speed == Speed && data.Rotation == Rotation && data.Rotate == Rotate && data.Pivot == Pivot)
			return true;
		else
			return false;
	}

} MotorData;

class MotorController : public I2CDevice
{
public:
	MotorController() : I2CDevice()
	{ }

	MotorController(const char* name, const uint8_t address)
		: I2CDevice(name, address)
	{ }

	void Update() override
	{
		if (m_SendTimer >= SENSOR_I2C_DELAY_MS && m_DataChanged)
		{
			SendMotorData(m_MotorData);
			m_SendTimer.Restart();
		}
	}

	void Move(int16_t degree, int16_t speed)
	{
		MotorData data(degree, speed, 0, false, 0);
		if (m_MotorData.Compare(data))
			return;
		m_MotorData = data;
		m_DataChanged = true;
	}

	void Rotate(int16_t speed, uint8_t pivot = 0)
	{
		MotorData data(0, speed, speed, true, pivot);
		if (m_MotorData.Compare(data))
			return;
		m_MotorData = data;
		m_DataChanged = true;
	}

	void SendMotorData(MotorData data)
	{
		Wire.beginTransmission(m_Address);

		Wire.write(CMD_MOTOR);
		Wire.write(((data.Degree >> 8) & 0xFF));
		Wire.write(data.Degree & 0xFF);

		Wire.write(((data.Speed >> 8) & 0xFF));
		Wire.write(data.Speed & 0xFF);
		
		Wire.write(((data.Rotation >> 8) & 0xFF));
		Wire.write(data.Rotation & 0xFF);

		Wire.write(data.Rotate ? 0x01 : 0x00);
		Wire.write(data.Pivot & 0xFF);

		Wire.endTransmission();
		m_DataChanged = false;
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
private:
	MotorData m_MotorData;
	Timer m_SendTimer;
	bool m_DataChanged = false;
};