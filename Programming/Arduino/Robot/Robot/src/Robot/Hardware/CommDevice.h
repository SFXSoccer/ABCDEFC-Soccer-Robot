#pragma once
#include "Device.h"

namespace Robot {

	class CommDevice : public Device
	{
	public:

		CommDevice()
			: Device(""), m_Serial(nullptr)
		{ }

		CommDevice(const char* name, HardwareSerial* serial)
			: Device(name), m_Serial(serial)
		{
#ifdef  COMM_SERIAL_BAUD
			m_Serial->begin(COMM_SERIAL_BAUD);
#else
			m_Serial->begin(9600);
#endif // COMM_SERIAL_BAUD

		}

		virtual void Send(uint8_t data[]) { }
		virtual void Recieve(uint8_t* data[]) { }

		virtual void Enable(bool enable) { m_Enabled = enable; }

		bool Enabled() const { return m_Enabled; }
		bool IsConnected() const { return m_Connected; }
		bool HasConnected() const { return m_HasConnected; }
	private:
		bool m_Enabled = false;
		bool m_Connected = false;
		bool m_HasConnected = false;

		HardwareSerial* m_Serial;
	};

}