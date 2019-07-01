#pragma once

#include "Definitions.h"
#include "TSOP.h"
#include "Robot/Hardware/I2C/TSOPSensorArray.h"

class IRSensorController : public Device
{
public:
	TSOP* IR0 = new TSOP("TSOP_0", 0);
	TSOP* IR1 = new TSOP("TSOP_1", 0);
	TSOP* IR2 = new TSOP("TSOP_2", 0);
	TSOP* IR3 = new TSOP("TSOP_3", 0);
	TSOP* IR4 = new TSOP("TSOP_4", 0);
	TSOP* IR5 = new TSOP("TSOP_5", 0);
	TSOP* IR6 = new TSOP("TSOP_6", 0);
	TSOP* IR7 = new TSOP("TSOP_7", 0);
	TSOP* IR8 = new TSOP("TSOP_8", 0);
	TSOP* IR9 = new TSOP("TSOP_9", 0);
	TSOP* IR10 = new TSOP("TSOP_10", 0);
	TSOP* IR11 = new TSOP("TSOP_11", 0);
	TSOP* IR12 = new TSOP("TSOP_12", 0);
	TSOP* IR13 = new TSOP("TSOP_13", 0);
	TSOP* IR14 = new TSOP("TSOP_14", 0);
	TSOP* IR15 = new TSOP("TSOP_15", 0);
	TSOP* IR16 = new TSOP("TSOP_16", 0);
	TSOP* IR17 = new TSOP("TSOP_17", 0);
	TSOP* IR18 = new TSOP("TSOP_18", 0);
	TSOP* IR19 = new TSOP("TSOP_19", 0);
	TSOP* IR20 = new TSOP("TSOP_20", 0);
	TSOP* IR21 = new TSOP("TSOP_21", 0);
	TSOP* IR22 = new TSOP("TSOP_22", 0);
	TSOP* IR23 = new TSOP("TSOP_23", 0);

	IRSensorController(const char* name)
		: Device(name)
	{
		m_OrderedList[0] = IR0;
		m_OrderedList[1] = IR1;
		m_OrderedList[2] = IR2;
		m_OrderedList[3] = IR3;
		m_OrderedList[4] = IR4;
		m_OrderedList[5] = IR5;
		m_OrderedList[6] = IR6;
		m_OrderedList[7] = IR7;
		m_OrderedList[8] = IR8;
		m_OrderedList[9] = IR9;
		m_OrderedList[10] = IR10;
		m_OrderedList[11] = IR11;
		m_OrderedList[12] = IR12;
		m_OrderedList[13] = IR13;
		m_OrderedList[14] = IR14;
		m_OrderedList[15] = IR15;
		m_OrderedList[16] = IR16;
		m_OrderedList[17] = IR17;
		m_OrderedList[18] = IR18;
		m_OrderedList[19] = IR19;
		m_OrderedList[20] = IR20;
		m_OrderedList[21] = IR21;
		m_OrderedList[22] = IR22;
		m_OrderedList[23] = IR23;
	}

	void Update()
	{
		m_SensorArray1->Update();
		m_SensorArray2->Update();
		m_SensorArray3->Update();

		m_OrderedList[0] = IR0;
		m_OrderedList[1] = IR1;
		m_OrderedList[2] = IR2;
		m_OrderedList[3] = IR3;
		m_OrderedList[4] = IR4;
		m_OrderedList[5] = IR5;
		m_OrderedList[6] = IR6;
		m_OrderedList[7] = IR7;
		m_OrderedList[8] = IR8;
		m_OrderedList[9] = IR9;
		m_OrderedList[10] = IR10;
		m_OrderedList[11] = IR11;
		m_OrderedList[12] = IR12;
		m_OrderedList[13] = IR13;
		m_OrderedList[14] = IR14;
		m_OrderedList[15] = IR15;
		m_OrderedList[16] = IR16;
		m_OrderedList[17] = IR17;
		m_OrderedList[18] = IR18;
		m_OrderedList[19] = IR19;
		m_OrderedList[20] = IR20;
		m_OrderedList[21] = IR21;
		m_OrderedList[22] = IR22;
		m_OrderedList[23] = IR23;

		for (int k = 0; k < SENSOR_TSOP_COUNT; k++)
		{
			m_OrderedList[k]->SetStrength(GetValue(k));
			TSOP* key = m_OrderedList[k];
			int i = k - 1;
			while ((i >= 0) && (key->GetStrength() <= m_OrderedList[i]->GetStrength()))
			{
				m_OrderedList[i + 1] = m_OrderedList[i];
				i--;
			}
			m_OrderedList[i + 1] = key;
		}
	}

	bool VerifyConnections()
	{
		Error::Report(Error::NONE, "Checking connections...", m_Name, m_ID); \

		bool connection1 = m_SensorArray1->VerifyConnection();
		bool connection2 = m_SensorArray2->VerifyConnection();
		bool connection3 = m_SensorArray3->VerifyConnection();

		Diagnostic::SetConnectedDevice(1, connection1);
		Diagnostic::SetConnectedDevice(2, connection2);
		Diagnostic::SetConnectedDevice(3, connection3);

		if (!connection1 || !connection2 || !connection3)
		{
			Error::Report(Error::FAILURE, "Problem with connecting to IR sensor arrays", m_Name, m_ID);
			Serial.print(m_SensorArray1->Name()); Serial.print(": "); Serial.println(connection1 ? "SUCCESS" : "FAIL");
			Serial.print(m_SensorArray2->Name()); Serial.print(": "); Serial.println(connection2 ? "SUCCESS" : "FAIL");
			Serial.print(m_SensorArray3->Name()); Serial.print(": "); Serial.println(connection3 ? "SUCCESS" : "FAIL");
			if (!connection1 && !connection2 && !connection3)
				Serial.println("Possible issue with connection to the board");
			else
				Serial.println("Possible issue with connections to IR sensor arrays");
			return false;
		}
		Error::Report(Error::NONE, "Connected with IR sensor arrays", m_Name, m_ID);
		return true;
	}

	uint16_t GetValue(int sensor) const
	{
		sensor = constrain(sensor, 0, SENSOR_TSOP_COUNT - 1);


		if (sensor < (SENSOR_TSOP_COUNT / 3))
			return m_SensorArray1->GetValue(sensor);
		else if (sensor < (SENSOR_TSOP_COUNT / 3) * 2)
			return m_SensorArray2->GetValue(sensor - (SENSOR_TSOP_COUNT / 3));
		else if (sensor < SENSOR_TSOP_COUNT)
			return m_SensorArray3->GetValue(sensor - (SENSOR_TSOP_COUNT / 3) * 2);
		return -1;
	}

	TSOP& operator[](int x) const { return *m_OrderedList[constrain(x, 0, SENSOR_TSOP_COUNT - 1)]; }
private:
	TSOPSensorArray* m_SensorArray1 = new TSOPSensorArray("IRSensor_1", ADDR_SENSOR_TSOP_ARRAY_1);
	TSOPSensorArray* m_SensorArray2 = new TSOPSensorArray("IRSensor_2", ADDR_SENSOR_TSOP_ARRAY_2);
	TSOPSensorArray* m_SensorArray3 = new TSOPSensorArray("IRSensor_3", ADDR_SENSOR_TSOP_ARRAY_3);

	TSOP* m_OrderedList[SENSOR_TSOP_COUNT];
};