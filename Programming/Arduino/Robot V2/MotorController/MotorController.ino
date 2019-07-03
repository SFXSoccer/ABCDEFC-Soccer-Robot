#include <Wire1.h>
#include "Definitions.h"
#include "Lightgate.h"
#include "Motor.h"
#include "Vector2f.h"

//
//				  NOTE
//		m_Motor4 is just the kicker
//		  motor and not used for 
//				movement
//


Lightgate* m_LightgateSensor;

Motor* m_Motor1;
Motor* m_Motor2;
Motor* m_Motor3;
Motor* m_Motor4;

void setup() 
{
	Wire1.begin(ADDRESS);
	Wire1.onReceive(receiveEvent);
	Wire1.onRequest(requestEvent);

	m_LightgateSensor = new Lightgate(PIN_LIGHTGATE_PWR, PIN_LIGHTGATE);
	m_Motor1 = new Motor(PIN_MOTOR_1_SPEED, PIN_MOTOR_1_DIRECTION, PIN_MOTOR_1_BRAKE, MOTOR_1_ANGLE);
	m_Motor2 = new Motor(PIN_MOTOR_2_SPEED, PIN_MOTOR_2_DIRECTION, PIN_MOTOR_2_BRAKE, MOTOR_2_ANGLE);
	m_Motor3 = new Motor(PIN_MOTOR_3_SPEED, PIN_MOTOR_3_DIRECTION, PIN_MOTOR_3_BRAKE, MOTOR_3_ANGLE);
	m_Motor4 = new Motor(PIN_MOTOR_4_SPEED, PIN_MOTOR_4_DIRECTION, PIN_MOTOR_4_BRAKE, MOTOR_4_ANGLE);

	pinMode(PIN_LIGHTGATE_PWR, OUTPUT);
	digitalWrite(PIN_LIGHTGATE_PWR, HIGH);
}

void loop() 
{
	Update();
}

void Update()
{
	m_LightgateSensor->Update();
}

void requestEvent()
{
	Wire1.write(m_LightgateSensor->CapturedBall());
}

void receiveEvent(int bytes)
{
	uint8_t cmd = Wire1.read();

	switch (cmd)
	{
	case CMD_MOTOR:
		if (bytes == 9)
		{
			uint8_t degreeHigh = Wire1.read();
			uint8_t degreeLow = Wire1.read();
			int16_t degree = (((degreeHigh & 0xFF) << 8) | (degreeLow & 0xFF));

			uint8_t speedHigh = Wire1.read();
			uint8_t speedLow = Wire1.read();
			int16_t speed = (((speedHigh & 0xFF) << 8) | (speedLow & 0xFF));

			uint8_t rotationHigh = Wire1.read();
			uint8_t rotationLow = Wire1.read();
			int16_t rotation = (((rotationHigh & 0xFF) << 8) | (rotationLow & 0xFF));

			bool rotate = Wire1.read() == 0x01 ? true : false;
			uint8_t pivot = Wire1.read();

			if (rotate)
			{
				m_Motor1->SetData(pivot == 1 ? 0 : abs(rotation), rotation >= 0 ? DIR_FORWARD : DIR_REVERSE, pivot != 1 && rotation == 0);
				m_Motor2->SetData(pivot == 2 ? 0 : abs(rotation), rotation >= 0 ? DIR_FORWARD : DIR_REVERSE, pivot != 2 && rotation == 0);
				m_Motor3->SetData(pivot == 3 ? 0 : abs(rotation), rotation >= 0 ? DIR_FORWARD : DIR_REVERSE, pivot != 3 && rotation == 0);
			}
			else
			{
				VectorMove(degree, speed);
			}
		}
		break;
	case CMD_LIGHTGATE:
		if (bytes == 2)
		{
			if (Wire1.read() == 0x00)
			{
				if (m_LightgateSensor->Active())
					m_LightgateSensor->Toggle();
			}
			else
			{
				if (!m_LightgateSensor->Active())
					m_LightgateSensor->Toggle();
			}
		}
		break;
	}

	while (Wire1.available())
		Wire1.read();
}

void VectorMove(int16_t degree, int16_t speed)
{
	Vector2f dir(degree);

	float motorAngles[3] = { MOTOR_1_ANGLE, MOTOR_2_ANGLE, MOTOR_3_ANGLE };

	for (int i = 0; i < 3; i++)
	{
		Vector2f vec(motorAngles[i]);
		int32_t velocity = vec * dir * speed;
		uint8_t newSpeed = abs(velocity);
		uint8_t newDir = velocity >= 0 ? DIR_FORWARD : DIR_REVERSE;
		bool newBrake = velocity == 0;

		if (i == 0)
			m_Motor1->SetData(newSpeed, newDir, newBrake);
		else if (i == 1)
			m_Motor2->SetData(newSpeed, newDir, newBrake);
		else if (i == 2)
			m_Motor3->SetData(newSpeed, newDir, newBrake);
	}
}