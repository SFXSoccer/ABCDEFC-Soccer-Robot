#pragma once

#include "I2CDevice.h"

#include "../../../../lib/Adafruit_Sensor/Adafruit_Sensor.h";
#include "../../../../lib/Adafruit_LSM303DLHC/Adafruit_LSM303_U.h";

class Magnetometer : public I2CDevice
{
public:
	Magnetometer() : I2CDevice()
	{}

	Magnetometer(const char* name, const uint8_t address)
		: I2CDevice(name, address)
	{
		m_Sensor.enableAutoRange(true);
		if (!m_Sensor.begin())
		{
			Error::Report(Error::FAILURE, "Failed to connect (timeout)", m_Name, m_ID);
			return;
		}

		SetRelative();
	}

	void Update() override
	{
		if (m_ReadTimer >= SENSOR_I2C_DELAY_MS)
		{
			ReadSensor();

			float heading = atan2(m_Y, m_X);
			heading += m_DeclinationAngle;

			if (heading < 0)
				heading += 2 * PI;
			if (heading > 2 * PI)
				heading -= 2 * PI;

			float headingDegrees = heading * 180 / M_PI;
			heading = headingDegrees;
			m_Heading = headingDegrees;
			m_RelativeHeading = heading - m_InitialHeading;

			if (m_RelativeHeading >= 180)
				m_RelativeHeading = m_RelativeHeading - 360;
			if (m_RelativeHeading <= -180)
				m_RelativeHeading = m_RelativeHeading + 360;

			m_ReadTimer.Restart();
		}
	}

	void SetRelative()
	{
		ReadSensor();

		float heading = atan2(m_Y, m_X);
		heading += m_DeclinationAngle;

		float headingDegrees = heading * 180 / M_PI;
		m_InitialHeading = headingDegrees;
	}

	void ReadSensor()
	{
		sensors_event_t event;
		m_Sensor.getEvent(&event);

		m_X = event.magnetic.x;
		m_Y = event.magnetic.y;
		m_Z = event.magnetic.z;
	}

	float X() const { return m_X; }
	float Y() const { return m_Y; }
	float Z() const { return m_Z; }

	float Heading() const { return m_Heading; }
	float Relative() const { return m_RelativeHeading; }
	float Initial() const { return m_InitialHeading; }

	operator float() const { return m_RelativeHeading; }
private:
	float m_X = 0.0f, m_Y = 0.0f, m_Z = 0.0f;
	float m_Heading = 0.0f;
	float m_RelativeHeading = 0.0f;
	float m_InitialHeading = 0.0f;

	// Set declination angle on your location and fix heading
	// You can find your declination on: http://magnetic-declination.com/
	// (+) Positive or (-) for negative
	// For Sydney, Australia declination angle is +12'35W (positive)
	// Formula: (deg + (min / 60.0)) / (180 / M_PI);
	const float m_DeclinationAngle = (12.0 + (35.0 / 60.0)) / (180 / M_PI);

	Adafruit_LSM303_Accel_Unified m_Sensor = Adafruit_LSM303_Accel_Unified(12345);
	Timer m_ReadTimer;
};