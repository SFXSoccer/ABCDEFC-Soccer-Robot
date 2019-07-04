#pragma once

#include "Definitions.h"
#include "Robot/Hardware/I2C/LightSensorArray.h"

typedef struct LightSensorCluster
{
	float Angle;
	float AngleMin;
	float AngleMax;

	LightSensorCluster() 
	{}

	LightSensorCluster(float angle, float min, float max)
		: Angle(angle), AngleMin(min), AngleMax(max)
	{ }
};

class LightSensorController : public Device
{
public:
	LightSensorController(const char* name)
		: Device(name)
	{ }

	void Update()
	{
		m_SensorArray1->Update();
		m_SensorArray2->Update();
		m_SensorArray3->Update();

		Diagnostic::SetLightSensorData(0, m_SensorArray1->GetCompressedValue());
		Diagnostic::SetLightSensorData(1, m_SensorArray2->GetCompressedValue());
		Diagnostic::SetLightSensorData(2, m_SensorArray3->GetCompressedValue());

		bool cluster = false;
		bool cluster1 = false;
		bool cluster2 = false;
		bool cluster3 = false;

		float angleMin = 0.0f;
		float angleMax = 0.0f;

		for (int i = 0; i < SENSOR_LIGHT_COUNT; i++)
		{
			if (GetValue(i) == 0x01)
			{
				angleMin = i * 15;
				cluster = true;
			}
			else if (GetValue(i) == 0x00)
			{
				if (cluster)
				{
					angleMax = i * 15;
					if (!cluster1)
					{
						LightSensorCluster c((angleMin + angleMax) / 2, angleMin, angleMax);
						m_Cluster1 = c;
					}
					else if (!cluster2)
					{
						LightSensorCluster c((angleMin + angleMax) / 2, angleMin, angleMax);
						m_Cluster2 = c;
					}
					else if (!cluster3)
					{
						LightSensorCluster c((angleMin + angleMax) / 2, angleMin, angleMax);
						m_Cluster3 = c;
					}
					cluster = false;
				}
			}
		}

		if (!cluster1)
			m_Cluster1.Angle = -1;
		if (!cluster2)
			m_Cluster2.Angle = -1;
		if (!cluster3)
			m_Cluster3.Angle = -1;
	}

	bool VerifyConnections()
	{
		Error::Report(Error::NONE, "Checking connections...", m_Name, m_ID);\

		bool connection1 = m_SensorArray1->VerifyConnection();
		bool connection2 = m_SensorArray2->VerifyConnection();
		bool connection3 = m_SensorArray3->VerifyConnection();

		Diagnostic::SetConnectedDevice(5, connection1);
		Diagnostic::SetConnectedDevice(6, connection2);
		Diagnostic::SetConnectedDevice(7, connection3);

		if (!connection1 || !connection2 || !connection3)
		{
			Error::Report(Error::FAILURE, "Problem with connecting to light sensor arrays", m_Name, m_ID);
			Serial.print(m_SensorArray1->Name()); Serial.print(": "); Serial.println(connection1 ? "SUCCESS" : "FAIL");
			Serial.print(m_SensorArray2->Name()); Serial.print(": "); Serial.println(connection2 ? "SUCCESS" : "FAIL");
			Serial.print(m_SensorArray3->Name()); Serial.print(": "); Serial.println(connection3 ? "SUCCESS" : "FAIL");
			if (!connection1 && !connection2 && !connection3)
				Serial.println("Possible issue with connection to the board");
			else
				Serial.println("Possible issue with connections to light sensor arrays");
			return false;
		}
		Error::Report(Error::NONE, "Connected with light sensor arrays", m_Name, m_ID);
		return true;
	}

	uint8_t GetValue(int sensor) const
	{
		if (sensor < (SENSOR_LIGHT_COUNT / 3))
			return m_SensorArray1->GetValue(sensor);
		else if (sensor < (SENSOR_LIGHT_COUNT / 3) * 2)
			return m_SensorArray2->GetValue(sensor - (SENSOR_LIGHT_COUNT / 3));
		else if (sensor < SENSOR_LIGHT_COUNT)
			return m_SensorArray3->GetValue(sensor - (SENSOR_LIGHT_COUNT / 3) * 2);
		return -1;
	}

	bool OnWhite()
	{
		return m_SensorArray1->OnWhite() || m_SensorArray2->OnWhite() || m_SensorArray3->OnWhite();
	}

	LightSensorCluster GetCluster(uint8_t cluster) const
	{
		if (cluster == 0)
			return m_Cluster1;
		else if (cluster == 1)
			return m_Cluster2;
		else if (cluster == 3)
			return m_Cluster3;
	}

	uint8_t operator[](int x) const { return GetValue(x); }
private:
	LightSensorArray* m_SensorArray1 = new LightSensorArray("LightSensor_1", ADDR_SENSOR_LIGHT_ARRAY_1);
	LightSensorArray* m_SensorArray2 = new LightSensorArray("LightSensor_2", ADDR_SENSOR_LIGHT_ARRAY_2);
	LightSensorArray* m_SensorArray3 = new LightSensorArray("LightSensor_3", ADDR_SENSOR_LIGHT_ARRAY_3);

	LightSensorCluster m_Cluster1;
	LightSensorCluster m_Cluster2;
	LightSensorCluster m_Cluster3;

};