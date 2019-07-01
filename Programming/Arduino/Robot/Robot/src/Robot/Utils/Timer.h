#pragma once

#include "../Core.h"

namespace Robot {

	class Timer
	{
	public:
		Timer();

		void Start();
		void Stop();
		void Reset();
		void Restart();

		long Elapsed() const;
		long Millis() const;
		double Seconds() const;

		bool IsRunning() const { return m_Stop == -1; }

		operator long() const { return Elapsed(); }
	private:
		long m_Start = 0;
		long m_Stop = -1;
		long m_Offset = 0;
	};

}