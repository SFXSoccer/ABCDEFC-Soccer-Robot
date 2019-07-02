#pragma once

#include "../../Core.h"
#include "../../OtherRobot.h"

class Communication : Device
{
public:
	Communication() : Device()
	{}

	Communication(const char* name, SoftwareSerial* serial) 
		: Device(name)
	{
		m_Serial = serial;

		m_Serial->begin(9600);
	}

	void Send(uint8_t data[])
	{
		m_Serial->write(COMM_PACKET_VERIFY);
		m_Serial->write(COMM_PACKET_START);

		for (int i = 0; i < COMM_PACKET_SIZE - 2; i++)
		{
			if (data[i] <= 255)
				m_Serial->write((byte)data[i]);
			else
			{
				m_Serial->write((byte)(data[i] & 0xFF));
				m_Serial->write((byte)((data[i] >> 8) & 0xFF));
			}
		}

		m_Serial->write(COMM_PACKET_END);
	}

	void Recieve(OtherRobot* robot)
	{
		if (!m_Serial->available())
			return;

		bool recieved = false;
		uint8_t verifyCode = m_Serial->read();
		uint8_t startCode = m_Serial->peek();

		if (verifyCode == COMM_PACKET_VERIFY && startCode == COMM_PACKET_START)
		{
			m_Serial->read();
			
			uint8_t data[COMM_PACKET_SIZE - 2];
			for (int i = 0; i < COMM_PACKET_SIZE - 3; i++)
				data[i] = m_Serial->read();
			
			robot->Mode = (PlayMode)data[0];
			robot->HasBall = data[1];
			robot->Playing = data[2];
			robot->IRDirection = data[3];

			if (m_Serial->read() == COMM_PACKET_END)
				recieved = true;
			m_PrevRecieve.Restart();
		}

		m_Connected = recieved || (m_PrevRecieve < COMMUNICATION_TIMEOUT);

		if (!m_Connected)
		{
			robot->Mode = PlayMode::Undecided;
			robot->HasBall = false;
			robot->Playing = false;
			robot->IRDirection = -1;
		}
		else
			m_HasConnected = true;
	}
private:
	SoftwareSerial* m_Serial;
	Timer m_PrevRecieve;

	bool m_Connected = false;
	bool m_HasConnected = false;
};