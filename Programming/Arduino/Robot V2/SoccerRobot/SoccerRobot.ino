//#define INIT_RUN
//#define SHOW_UPS

#include "SoccerRobot.h"

void Begin()
{
	
}

void End()
{
	Motors->Rotate(0);
}

void Run()
{
	for (int i = 0; i < 24; i++)
	{
		if (i < 23)
		{
			Serial.print(IRSensors->GetValue(i));
			Serial.print(", ");
		}
		else
			Serial.println(IRSensors->GetValue(i));
	}
}