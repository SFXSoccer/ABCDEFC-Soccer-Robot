#pragma once

#include <Arduino.h>

class Error 
{
public:
	enum ErrorStatus : uint8_t
	{
		NONE		= 0,
		WARNING		= 1,
		CRITICAL	= 2,
		FAILURE		= 3
	};

	static void Report(ErrorStatus status, const char* msg);
	static void Report(ErrorStatus status, const char* msg, const char* name, const int id);
	static ErrorStatus GetStatus() { return m_ErrorStatus; }
private:
	static ErrorStatus m_ErrorStatus;
};