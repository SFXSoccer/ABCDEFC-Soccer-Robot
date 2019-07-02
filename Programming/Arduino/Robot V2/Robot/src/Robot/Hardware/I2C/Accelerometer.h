#pragma once

#include "I2CDevice.h"

#include "../../../lib/Adafruit_Sensor/Adafruit_Sensor.h"
#include "../../../lib/Adafruit_LSM303DLHC/Adafruit_LSM303_U.h"

class Accelerometer : public I2CDevice
{
public:
	Accelerometer() : I2CDevice()
	{ }

	Accelerometer(const char* name, const uint8_t address)
		: I2CDevice(name, address)
	{
		if (!m_Sensor.begin())
		{
			Error::Report(Error::FAILURE, "Failed to connect (timeout)", m_Name, m_ID);
			return;
		}
	}

	void Update() override
	{
		if (m_ReadTimer >= SENSOR_I2C_DELAY_MS)
		{
			sensors_event_t event;
			m_Sensor.getEvent(&event);

			m_X = event.acceleration.x;
			m_Y = event.acceleration.y;
			m_Z = event.acceleration.z;

			m_ReadTimer.Restart();
		}
	}

	float X() const { return m_X; }
	float Y() const { return m_Y; }
	float Z() const { return m_Z; }
private:
	float m_X = 0.0f, m_Y = 0.0f, m_Z = 0.0f;
	Adafruit_LSM303_Accel_Unified m_Sensor = Adafruit_LSM303_Accel_Unified(54321);
	Timer m_ReadTimer;
};