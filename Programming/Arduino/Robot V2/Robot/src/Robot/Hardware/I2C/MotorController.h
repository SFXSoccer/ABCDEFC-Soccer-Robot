#pragma once

#include "I2CDevice.h"

class MotorController : public I2CDevice
{
public:
	MotorController() : I2CDevice()
	{ }

	MotorController(const char* name, const uint8_t address)
		: I2CDevice(name, address)
	{ }

	void Set(uint8_t motor, int16_t speed)
	{
		motor = constrain(motor, 0, 3);
		speed = constrain(speed, -255, 255);

		if (abs(speed) > 0)
		{
			Wire.beginTransmission(m_Address);
			Wire.write(CMD_MOTOR_1 + motor);
			Wire.write(abs(speed & 0xFF));
			Wire.write(speed > 0 ? MOTOR_DIR_FORWARD : MOTOR_DIR_REVERSE);
			Wire.write(0x00);
			Wire.endTransmission();
		}
		else
			Stop(motor);
	}

	void Stop(uint8_t motor)
	{
		motor = constrain(motor, 0, 3);

		Wire.beginTransmission(m_Address);
		Wire.write(CMD_MOTOR_1 + motor);
		Wire.write(0x00);
		Wire.write(MOTOR_DIR_FORWARD);
		Wire.write(0x01);
		Wire.endTransmission();
	}

	void Rotate(int16_t speed)
	{
		speed = constrain(speed, -255, 255);

		Wire.beginTransmission(m_Address);
		Wire.write(CMD_MOTOR_ALL);
		Wire.write(abs(speed));
		Wire.write(speed >= 0 ? MOTOR_DIR_FORWARD : MOTOR_DIR_REVERSE);
		Wire.write(speed == 0 ? 0x01 : 0x00);
		Wire.endTransmission();
	}

	void Move(int16_t degree, uint8_t speed)
	{
		degree = constrain(degree, -360, 360);
		speed = constrain(speed, 0, 255);

		Wire.beginTransmission(m_Address);
		Wire.write(CMD_MOVE);
		Wire.write(((degree >> 8) & 0xFF));
		Wire.write(degree & 0xFF);
		Wire.write(speed);
		Wire.endTransmission();
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

	void Update() override
	{}
};