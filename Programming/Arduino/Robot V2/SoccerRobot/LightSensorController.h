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

		CalculateClusters();
	}

	void CalculateClusters()
	{
		m_Cluster1 = LightSensorCluster(-1, -1, -1);
		m_Cluster2 = LightSensorCluster(-1, -1, -1);
		m_Cluster3 = LightSensorCluster(-1, -1, -1);

		bool cluster1Done = false;
		bool cluster2Done = false;
		bool cluster3Done = false;

		for (int i = 0; i < SENSOR_LIGHT_COUNT; i++)
		{
			if (!cluster1Done)
			{
				if (GetValue(i) == 0x01)
				{
					if (m_Cluster1.AngleMin == -1)
						m_Cluster1.AngleMin = i * 15;
					else
						m_Cluster1.AngleMax = i * 15;
				}
				else if (m_Cluster1.AngleMin != -1)
				{
					m_Cluster1.Angle = m_Cluster1.AngleMax > -1 ? (m_Cluster1.AngleMin + m_Cluster1.AngleMax) / 2 : m_Cluster1.AngleMin;
					cluster1Done = true;
				}
			}
			else if (!cluster2Done)
			{
				if (GetValue(i) == 0x01)
				{
					if (m_Cluster2.AngleMin == -1)
						m_Cluster2.AngleMin = i * 15;
					else
						m_Cluster2.AngleMax = i * 15;

					if (i == SENSOR_LIGHT_COUNT - 1 && GetValue(0) == 0x01)
					{
						m_Cluster1.AngleMin = m_Cluster2.AngleMin - 360;
						m_Cluster1.Angle = m_Cluster1.AngleMax > -1 ? (m_Cluster1.AngleMin + m_Cluster1.AngleMax) / 2 : m_Cluster1.AngleMin;
						m_Cluster2 = LightSensorCluster(-1, -1, -1);
					}
				}
				else if (m_Cluster2.AngleMin != -1)
				{
					m_Cluster2.Angle = m_Cluster2.AngleMax > -1 ? (m_Cluster2.AngleMin + m_Cluster2.AngleMax) / 2 : m_Cluster2.AngleMin;
					cluster2Done = true;
				}
			}
			else if (!cluster3Done)
			{
				if (GetValue(i) == 0x01)
				{
					if (m_Cluster3.AngleMin == -1)
						m_Cluster3.AngleMin = i * 15;
					else
						m_Cluster3.AngleMax = i * 15;

					if (i == SENSOR_LIGHT_COUNT - 1 && GetValue(0) == 0x01)
					{
						m_Cluster1.AngleMin = m_Cluster3.AngleMin - 360;
						m_Cluster1.Angle = m_Cluster1.AngleMax > -1 ? (m_Cluster1.AngleMin + m_Cluster1.AngleMax) / 2 : m_Cluster1.AngleMin;
						m_Cluster3 = LightSensorCluster(-1, -1, -1);
					}
				}
				else if (m_Cluster3.AngleMin != -1)
				{
					m_Cluster3.Angle = m_Cluster3.AngleMax > -1 ? (m_Cluster3.AngleMin + m_Cluster3.AngleMax) / 2 : m_Cluster3.AngleMin;
					cluster3Done = true;
				}
			}
		}
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