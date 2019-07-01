#include <Wire1.h>
#include "Definitions.h"

int8_t m_CapReset = 0;
int32_t m_SensorValues[SENSOR_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void setup()
{
	Wire1.begin(ADDRESS);
	Wire1.onReceive(receiveEvent);
	Wire1.onRequest(requestEvent);

	pinMode(LED_STATUS, OUTPUT);
	pinMode(PIN_POWER, OUTPUT);

	digitalWrite(LED_STATUS, HIGH);
	digitalWrite(PIN_POWER, HIGH);
}

void loop()
{
	Update();
}

void Update()
{
	m_SensorValues[0] = analogRead(PIN_SENSOR_1);
	m_SensorValues[1] = analogRead(PIN_SENSOR_2);
	m_SensorValues[2] = analogRead(PIN_SENSOR_3);
	m_SensorValues[3] = analogRead(PIN_SENSOR_4);
	m_SensorValues[4] = analogRead(PIN_SENSOR_5);
	m_SensorValues[5] = analogRead(PIN_SENSOR_6);
	m_SensorValues[6] = analogRead(PIN_SENSOR_7);
	m_SensorValues[7] = analogRead(PIN_SENSOR_8);

	if (m_CapReset > 255)
	{
		digitalWrite(PIN_POWER, LOW);
		delay(2);
		digitalWrite(PIN_POWER, HIGH);
		m_CapReset = 0;
	}
	m_CapReset++;
}

void requestEvent()
{
	uint8_t buffer[SENSOR_COUNT * 2];
	int s = 0;
	for (int i = 0; i < SENSOR_COUNT * 2; i += 2)
	{
		buffer[i] = ((m_SensorValues[s] >> 8) & 0xFF);
		buffer[i + 1] = m_SensorValues[s] & 0xFF;
		s++;
	}

	Wire1.write(buffer, SENSOR_COUNT * 2);
}

void receiveEvent(int bytes)
{

}