#pragma once

#include "../../Core.h"

class Communication : Device
{
public:
	Communication() : Device()
	{}

	Communication(const char* name, SoftwareSerial serial) 
		: Device(name)
	{
		m_Serial = &serial;
	}
private:
	SoftwareSerial* m_Serial;
};