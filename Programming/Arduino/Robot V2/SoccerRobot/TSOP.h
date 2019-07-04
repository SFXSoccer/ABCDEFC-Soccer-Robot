#pragma once

#include "Robot/Hardware/Device.h"

class TSOP : public Device
{
public:
	TSOP(const char* name, float angle)
		: Device(name), m_Angle(angle)
	{ }

	void SetStrength(uint8_t value) { m_Strength = value; }

	uint16_t GetStrength() const { return m_Strength; }
	float GetAngle() const { return m_Angle; }
private:
	uint8_t m_Strength = 0;
	float m_Angle = 0.0f;
};