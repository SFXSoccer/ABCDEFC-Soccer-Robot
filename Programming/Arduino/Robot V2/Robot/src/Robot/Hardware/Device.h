#pragma once

#include "../Core.h"

class Device
{
public:
	Device()
		: m_Name(""), m_ID(m_PrevID++)
	{ }

	Device(const char* name)
		: m_Name(name), m_ID(m_PrevID++)
	{ }

	const char* Name() const { return m_Name; }
	int ID() const { return m_ID; }
protected:
	const char* m_Name;
	const int m_ID;
private:
	static int m_PrevID;
};

int Device::m_PrevID = 0;