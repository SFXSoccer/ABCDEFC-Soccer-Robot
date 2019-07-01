#include <Wire1.h>
#include "Definitions.h"
#include "LightSensor.h"

LightSensor* m_SensorValues[SENSOR_COUNT];

void setup()
{
	Wire1.begin(ADDRESS);
	Wire1.onReceive(receiveEvent);
	Wire1.onRequest(requestEvent);

	m_SensorValues[0] = new LightSensor(PIN_SENSOR_1);
	m_SensorValues[1] = new LightSensor(PIN_SENSOR_2);
	m_SensorValues[2] = new LightSensor(PIN_SENSOR_3);
	m_SensorValues[3] = new LightSensor(PIN_SENSOR_4);
	m_SensorValues[4] = new LightSensor(PIN_SENSOR_5);
	m_SensorValues[5] = new LightSensor(PIN_SENSOR_6);
	m_SensorValues[6] = new LightSensor(PIN_SENSOR_7);
	m_SensorValues[7] = new LightSensor(PIN_SENSOR_8);

	pinMode(LED_STATUS, OUTPUT);
	digitalWrite(LED_STATUS, HIGH);
}

void loop() 
{
	Update();
}

void Update()
{
	m_SensorValues[0]->Update();
	m_SensorValues[1]->Update();
	m_SensorValues[2]->Update();
	m_SensorValues[3]->Update();
	m_SensorValues[4]->Update();
	m_SensorValues[5]->Update();
	m_SensorValues[6]->Update();
	m_SensorValues[7]->Update();
}

void requestEvent()
{

	/*uint8_t buffer[SENSOR_COUNT];
	for (int i = 0; i < SENSOR_COUNT; i++)
		buffer[i] = m_SensorValues[i]->GetValue();*/

	uint8_t data = 0x00;
	for (int i = 0; i < SENSOR_COUNT; i++)
		data |= m_SensorValues[i]->GetValue() << SENSOR_COUNT - (i + 1);

	Wire1.write(data);
}

void receiveEvent(int bytes)
{ 

}