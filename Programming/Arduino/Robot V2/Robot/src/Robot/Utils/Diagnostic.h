#pragma once

#include "../Core.h"

class Diagnostic
{
public:
	static void ReadData(uint8_t* data);
	static void SendData();

	static void SetConnectedDevice(uint8_t device, bool connected)
	{
		m_ConnectedDevices ^= (-(connected ? 1 : 0) ^ m_ConnectedDevices) & (1UL << device);
	}

	static void SetLightSensorData(uint8_t array, uint8_t data)
	{
		m_LightData[array] = data;
	}

	static bool Running() { return m_Running; }
private:
	static bool m_Running;
	static uint8_t m_ConnectedDevices;
	static uint8_t m_LightData[3];
};