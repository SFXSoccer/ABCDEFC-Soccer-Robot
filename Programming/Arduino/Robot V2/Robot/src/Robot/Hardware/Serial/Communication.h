#pragma once

#include "../../Core.h"
#include "../../OtherRobot.h"

class Communication : Device
{
public:
	Communication() : Device()
	{}

	Communication(const char* name) 
		: Device(name)
	{
		Serial3.begin(9600);
	}

	void Update(OtherRobot* robot, uint8_t data[], bool dontRecieve = false)
	{

		if (m_Enabled/* && t_prevUpdate > COMM_SERIAL_DELAY*/)
		{
			Send(data);
			if (!dontRecieve)
				Recieve(robot);
		}
	}

	void Send(uint8_t data[])
	{
		Serial3.write(COMM_PACKET_VERIFY);
		Serial3.write(COMM_PACKET_START);

		for (int i = 0; i < COMM_PACKET_SIZE - 2; i++)
		{
			if (data[i] <= 255)
				Serial3.write((byte)data[i]);
			else
			{
				Serial3.write((byte)(data[i] & 0xFF));
				Serial3.write((byte)((data[i] >> 8) & 0xFF));
			}
		}

		Serial3.write(COMM_PACKET_END);
	}

	void Recieve(OtherRobot* robot)
	{
		if (!Serial3.available())
			return;

		bool recieved = false;
		uint8_t verifyCode = Serial3.read();
		uint8_t startCode = Serial3.peek();

		if (verifyCode == COMM_PACKET_VERIFY && startCode == COMM_PACKET_START)
		{
			Serial3.read();
			
			uint8_t data[COMM_PACKET_SIZE - 2];
			for (int i = 0; i < COMM_PACKET_SIZE - 3; i++)
				data[i] = Serial3.read();
			
			robot->Mode = (PlayMode)data[0];
			robot->HasBall = data[1];
			robot->Playing = data[2];
			robot->IRDirection = data[3];

			if (Serial3.read() == COMM_PACKET_END)
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

	void SetEnabled(bool enabled)
	{
		m_Enabled = enabled;
	}
private:
	Timer m_PrevRecieve;

	bool m_Enabled = true;
	bool m_Connected = false;
	bool m_HasConnected = false;
};