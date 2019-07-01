#include "Diagnostic.h"

bool Diagnostic::m_Running = false;
uint8_t Diagnostic::m_ConnectedDevices = 0x00;
uint8_t Diagnostic::m_LightData[3] = { 0x00, 0x00, 0x00 };

#define STARTBYTE	0xA0
#define ENDBYTE		0xA1

void Diagnostic::ReadData(uint8_t* data)
{
	switch (data[0])
	{
	case CMD_DIAGNOSTIC_START:
		m_Running = true;
		break;
	case CMD_DIAGNOSTIC_STOP:
		m_Running = false;
		break;
	case CMD_DIAGNOSTIC_I2C_SCAN:
		Serial.write(STARTBYTE);
		Serial.write(CMD_DIAGNOSTIC_I2C_SCAN);
		for (uint8_t address = 1; address < 127; address++)
		{
			// The i2c_scanner uses the return value of
			// the Write.endTransmisstion to see if
			// a device did acknowledge to the address.
			Wire.beginTransmission(address);
			uint8_t error = Wire.endTransmission();

			if (error == 0)
				Serial.write(address);
		}
		Serial.write(ENDBYTE);
	default:
		break;
	}
}

void Diagnostic::SendData()
{
	Serial.write(STARTBYTE);
	Serial.write(0x00);
	Serial.write(m_ConnectedDevices);
	Serial.write(ENDBYTE);
}