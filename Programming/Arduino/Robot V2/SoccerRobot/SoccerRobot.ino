//#define INIT_RUN
//#define SHOW_UPS

#define ROBOT_ATTACK

#include "SoccerRobot.h"

Timer KickEnd;
bool kick = false;

void Begin()
{

}

void End()
{

}

void Run()
{
	StatusLED->Write(IRSensors->Cluster().Size > 3);
	Serial.println(IRSensors->Cluster().Angle);
	delay(10);
	return;
	SetMotorCompassOffset(14, 1);

	if (!LightSensors->OnWhite())
	{
		if (IRSensors->Direction() == -1)
		{
			Center();
		}
		else if (IRSensors->Direction() >= 11 && IRSensors->Direction() <= 13)
		{
			GetToBall();
		}
		else
		{
			Orbit();
		}
	}
	else
	{
		Motors->Move(-(LightSensors->GetCluster(0).Angle - 180) + 180, 255);
	}

	bool onWhite = LightSensors->OnWhite();

	if (onWhite)
		StatusLED->Write(HIGH);
	else
		StatusLED->Write(LOW);
}

void GetToBall()
{
	if (LightgateSensor->GetValue())
	{
		if (Cam->OpposingGoal().Detected())
		{
			if (Cam->OpposingGoal().CenterX - (CAMERA_IMAGE_WIDTH / 2) > 10)
			{
				Motors->Move(45, 255);
			}
			else if (Cam->OpposingGoal().CenterX - (CAMERA_IMAGE_WIDTH / 2) < -10)
			{
				Motors->Move(-45, 255);
			}
			else
			{
				Motors->Move(0, 255);
			}
		}
		else
		{
			Motors->Move(0, 255);
		}
		return;
	}

	if (IRSensors->Direction() == 11)
		Motors->Move(25, 255);
	else if (IRSensors->Direction() == 13)
		Motors->Move(-25, 255);
	else
		Motors->Move(0, 255);
}

void Orbit()
{
	uint8_t ir = IRSensors->Direction();
	if (ir >= 0 && ir <= 4)
		Move(-137, 255);
	else if (ir <= 23 && ir >= 19)
		Move(137, 255);
	else if (ir >= 5 && ir <= 6)
		Move(180, 255);
	else if (ir <= 18 && ir >= 17)
		Move(180, 255);
	else if (ir >= 7 && ir <= 10)
		Move(137, 255);
	else if (ir <= 16 && ir >= 14)
		Move(-137, 255);
	else if (ir == 11)
		Move(90, 255);
	else if (ir == 13)
		Move(-90, 255);
}

void Move(int16_t degree, int16_t speed)
{
	/*if (CAMERA_IMAGE_WIDTH - Cam->FriendlyGoal().Width < 10)
	{
		if (degree > 90)
			degree = -90;
		else if (degree < -90)
			degree = 90;
	}*/

	Motors->Move(degree, speed);
}

void Center()
{
	if (abs(Compass->Relative()) < 6)
	{
		if (Cam->OpposingGoal().Detected())
		{
			if (Cam->OpposingGoal().CenterX - (CAMERA_IMAGE_WIDTH / 2) > 10)
			{
				if (!Cam->FriendlyGoal().Detected())
					Motors->Move(45, 140);
				else
					Motors->Move(90, 140);
			}
			else if (Cam->OpposingGoal().CenterX - (CAMERA_IMAGE_WIDTH / 2) < -10)
			{
				if (!Cam->FriendlyGoal().Detected())
					Motors->Move(-45, 140);
				else
					Motors->Move(-90, 140);
			}
			else
			{
				Motors->Rotate(0);
			}
		}
		else if (Cam->FriendlyGoal().Detected())
		{
			if (Cam->FriendlyGoal().CenterX - (CAMERA_IMAGE_WIDTH / 2) > 10)
			{
				if (!Cam->OpposingGoal().Detected())
					Motors->Move(135, 140);
				else
					Motors->Move(90, 140);
			}
			else if (Cam->FriendlyGoal().CenterX - (CAMERA_IMAGE_WIDTH / 2) < -10)
			{
				if (!Cam->OpposingGoal().Detected())
					Motors->Move(-135, 140);
				else
					Motors->Move(-90, 140);
			}
			else
			{
				Motors->Rotate(0);
			}
		}
	}
	else
	{
		Motors->Rotate(0);
	}
}

void SetMotorCompassOffset(int range, int multiplier)
{
	float c = Compass->Relative();

	int i = 80;
	int m = 10;
	int inverse = (c < 0) ? 1 : -1;
	float a = (m - i) / 4;
	float k = a + i;
	int vc = (a * (2 * cos((2 * M_PI * c) / 360) + pow(cos((2 * M_PI * c) / 360), 2)) + k) * inverse;

	if (c < -(range / 2) || c > range / 2) Motors->SetOffset(vc);
	else Motors->SetOffset(0);
}