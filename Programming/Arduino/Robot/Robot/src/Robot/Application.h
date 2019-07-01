#pragma once

#include "Core.h"
#include "Hardware/Digital/DigitalDevice.h"
#include "Hardware/CommDevice.h"

namespace Robot {

	class Application
	{
	public:
		virtual void Begin() { };
		virtual void End() { };
		virtual void Run() = 0;

		void Start();
		void Stop();

		void SetStartDevice(DigitalDevice* device) { m_StartDevice = device; }
		void SetStopDevice(DigitalDevice* device) { m_StopDevice = device; }

		void SetCommStartDevice(DigitalDevice* device) { m_CommStartDevice = device; }
		void SetCommStopDevice(DigitalDevice* device) { m_CommStopDevice = device; }
		void SetCommDevice(CommDevice* device) { m_CommDevice = device; }

		DigitalDevice GetStartDevice() const { return *m_StartDevice; }
		DigitalDevice GetStopDevice() const { return *m_StopDevice; }

		DigitalDevice GetCommStartDevice() const { return *m_CommStartDevice; }
		DigitalDevice GetCommStopDevice() const { return *m_CommStopDevice; }
		CommDevice GetCommDevice() const { return *m_CommDevice; }

		bool IsRunning() { return m_Running; }
	private:
		DigitalDevice* m_StartDevice;
		DigitalDevice* m_StopDevice;

		DigitalDevice* m_CommStartDevice;
		DigitalDevice* m_CommStopDevice;
		CommDevice* m_CommDevice;

#ifdef INIT_RUN
		bool m_Running = true;
#else
		bool m_Running = false;
#endif // INIT_RUN
	};
	
	// To be defined in client
	Application* CreateApplication();
}