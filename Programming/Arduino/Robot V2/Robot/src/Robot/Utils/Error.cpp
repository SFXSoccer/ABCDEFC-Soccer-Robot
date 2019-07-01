#include "Error.h"

Error::ErrorStatus Error::m_ErrorStatus = Error::NONE;

void Error::Report(ErrorStatus status, const char* msg)
{
	m_ErrorStatus = (m_ErrorStatus != FAILURE) ? status : m_ErrorStatus;
	Serial.print("[");
	Serial.print((status == NONE ? "INFO" :
				  status == WARNING ? "WARN" :
				  status == CRITICAL ? "CRIT" :
				  status == FAILURE ? "FAIL" :
				  "????"));
	Serial.print("]: ");
	Serial.println(msg);
}

void Error::Report(ErrorStatus status, const char* msg, const char* name, const int id)
{
	Serial.print("[\"");
	Serial.print(name);
	Serial.print("\" (ID: ");
	Serial.print(id, DEC);
	Serial.print(")]");
	Report(status, msg);
}
