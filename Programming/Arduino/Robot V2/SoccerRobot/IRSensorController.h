#pragma once

#include "Definitions.h"
#include "Robot/Hardware/I2C/TSOPSensorArray.h"

typedef struct IRSensorCluster
{
	int Center;
	int Min;
	int Max;
	int Size;

	float Angle;
	float AngleMin;
	float AngleMax;

	IRSensorCluster()
	{}

	IRSensorCluster(int min, int max)
		: Min(min), Max(max)
	{
		Center = (min + max) / (min != max ? 2 : 1);
		Size = max - min;
		AngleMin = min * 15;
		AngleMax = max * 15;
		Angle = (AngleMin + AngleMax) / (min != max ? 2 : 1);
	}
};

class IRSensorController : public Device
{
public:
	IRSensorController(const char* name)
		: Device(name)
	{ }

	void Update()
	{
		m_SensorArray1.Update();
		m_SensorArray2.Update();
		m_SensorArray3.Update();

		CalculateCluster();
	}

	void CalculateCluster()
	{
		uint8_t first = 0;
		uint8_t last = 0;
		uint8_t count = 0;
		uint8_t total = 0;
		uint8_t highcount = 0;
		uint8_t hightotal = 0;
		bool cluster = false;
		for (int i = 0; i < SENSOR_TSOP_COUNT; i++)
		{
			uint8_t value = GetValue(i);
			if (value)
			{
				if (!cluster)
					first = i;
				count++;
				total += i;
				cluster = true;
			}
			if (!value && cluster)
			{
				if (count > highcount)
				{
					last = i;
					m_Cluster = IRSensorCluster(first, last);
					highcount = count;
					hightotal = total;
					count = 0;
					total = 0;
				}
				cluster = false;
			}
			else if (i == SENSOR_TSOP_COUNT - 1 && cluster && GetValue(0) == 0x01)
			{
				i = 0;
				first = first - SENSOR_TSOP_COUNT;
			}
		}

		if (highcount == 0)
			m_Direction = -1;
		else
			m_Direction = hightotal / highcount;
	}

	IRSensorCluster Cluster() const
	{
		return m_Cluster;
	}

	bool VerifyConnections()
	{
		Error::Report(Error::NONE, "Checking connections...", m_Name, m_ID); \

		bool connection1 = m_SensorArray1.VerifyConnection();
		bool connection2 = m_SensorArray2.VerifyConnection();
		bool connection3 = m_SensorArray3.VerifyConnection();

		Diagnostic::SetConnectedDevice(1, connection1);
		Diagnostic::SetConnectedDevice(2, connection2);
		Diagnostic::SetConnectedDevice(3, connection3);

		if (!connection1 || !connection2 || !connection3)
		{
			Error::Report(Error::FAILURE, "Problem with connecting to IR sensor arrays", m_Name, m_ID);
			Serial.print(m_SensorArray1.Name()); Serial.print(": "); Serial.println(connection1 ? "SUCCESS" : "FAIL");
			Serial.print(m_SensorArray2.Name()); Serial.print(": "); Serial.println(connection2 ? "SUCCESS" : "FAIL");
			Serial.print(m_SensorArray3.Name()); Serial.print(": "); Serial.println(connection3 ? "SUCCESS" : "FAIL");
			if (!connection1 && !connection2 && !connection3)
				Serial.println("Possible issue with connection to the board");
			else
				Serial.println("Possible issue with connections to IR sensor arrays");
			return false;
		}
		Error::Report(Error::NONE, "Connected with IR sensor arrays", m_Name, m_ID);
		return true;
	}

	uint8_t GetValue(int sensor) const
	{
		sensor = constrain(sensor, 0, SENSOR_TSOP_COUNT - 1);

		if (sensor < (SENSOR_TSOP_COUNT / 3))
			return m_SensorArray1.GetValue(sensor);
		else if (sensor < (SENSOR_TSOP_COUNT / 3) * 2)
			return m_SensorArray2.GetValue(sensor - (SENSOR_TSOP_COUNT / 3));
		else if (sensor < SENSOR_TSOP_COUNT)
			return m_SensorArray3.GetValue(sensor - (SENSOR_TSOP_COUNT / 3) * 2);
		return -1;
	}

	int8_t Direction() const { return m_Direction; }
	uint8_t operator[](int x) const { return GetValue(x); }
private:
	TSOPSensorArray m_SensorArray1 = TSOPSensorArray("IRSensor_1", ADDR_SENSOR_TSOP_ARRAY_1);
	TSOPSensorArray m_SensorArray2 = TSOPSensorArray("IRSensor_2", ADDR_SENSOR_TSOP_ARRAY_2);
	TSOPSensorArray m_SensorArray3 = TSOPSensorArray("IRSensor_3", ADDR_SENSOR_TSOP_ARRAY_3);

	IRSensorCluster m_Cluster;
	int8_t m_Direction = -1;
};