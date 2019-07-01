#pragma once

#include "Definitions.h"

class Motor
{
public:
	Motor(uint8_t speed, uint8_t direction, uint8_t brake, float angle)
		: m_PinSpeed(speed), m_PinDirection(direction), m_PinBrake(brake), m_Angle(angle)
	{
		pinMode(m_PinSpeed, OUTPUT);
		pinMode(m_PinDirection, OUTPUT);
		pinMode(m_PinBrake, OUTPUT);

		m_Offset = 0;

		Set(0);
	}

	void SetData(uint8_t speed, uint8_t direction, bool brake)
	{
		if (brake)
			Stop();
		else
			Set(speed * (direction == DIR_FORWARD ? 1 : -1));
	}

	void Set(int16_t velo)
	{
		if (m_Braked)
			Brake(!m_Braked);

		//velo += m_Offset;
		velo = constrain(velo, -255, 255);

		if (velo < 0)
		{
			digitalWrite(m_PinDirection, m_Direction = DIR_REVERSE);
			analogWrite(m_PinSpeed, m_Speed = abs(velo));
		}
		else if (velo > 0)
		{
			digitalWrite(m_PinDirection, m_Direction = DIR_FORWARD);
			analogWrite(m_PinSpeed, m_Speed = abs(velo));
		}
		else
		{
			digitalWrite(m_PinDirection, m_Direction = DIR_FORWARD);
			analogWrite(m_PinSpeed, m_Speed = 0);
		}
	}

	void SetDir(uint8_t direction)
	{
		if (direction == DIR_FORWARD)
			Set(m_Speed);
		else
			Set(-m_Speed);
	}

	void Brake(bool brake = true)
	{
		digitalWrite(m_PinBrake, brake ? HIGH : LOW);
		m_Braked = brake;
	}

	void SetOffset(int16_t offset)
	{
		m_Offset = constrain(offset, -255, 255);
	}

	void Stop()
	{
		SetOffset(0);
		Brake();
		Set(0);
	}

	bool IsBraked() const { return m_Braked; }
	uint8_t GetSpeed() const { return m_Speed; }
	uint16_t GetSpeedDir() const { return m_Speed * (m_Direction == DIR_FORWARD ? 1 : -1); }
	uint8_t GetDirection() const { return m_Direction; }
	float GetAngle() const { return m_Angle; }

	void operator=(int16_t velo) { Set(velo); }
	operator uint16_t() { return GetSpeedDir(); }
private:
	uint8_t m_PinSpeed = 0;
	uint8_t m_PinDirection = 0;
	uint8_t m_PinBrake = 0;

	uint8_t m_Speed = 0;
	uint8_t m_Direction = DIR_FORWARD;
	int16_t m_Offset = 0;

	float m_Angle = 0.0f;
	bool m_Braked = false;
};