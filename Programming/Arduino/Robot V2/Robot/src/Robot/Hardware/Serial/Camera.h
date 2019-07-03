#pragma once

#include "../Device.h"

enum GoalColor
{
	None, Yellow, Blue
};

typedef struct GoalData
{
	uint8_t CenterX;
	uint8_t CenterY;
	uint8_t Width;
	uint8_t Height;

	GoalData()
	{ }

	GoalData(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
		: CenterX(x), CenterY(y), Width(width), Height(height)
	{ }
} GoalData;

class Camera : public Device
{
public:
	Camera() : Device()
	{ }

	Camera(const char* name)
		: Device(name)
	{
		Serial4.begin(19200);
	}

	void Update()
	{
		if (Serial4.available() >= 10)
		{
			Serial.println("Test");
			if (Serial4.read() == CMD_CAMERA)
			{
				for (int i = 0; i < 2; i++)
				{
					uint8_t cx = Serial4.read();
					uint8_t cy = Serial4.read();
					uint8_t w = Serial4.read();
					uint8_t h = Serial4.read();

					if (i == 0)
					{
						GoalData yellow(cx, cy, w, h);
						YellowGoal = yellow;
					}
					else
					{
						GoalData blue(cx, cy, w, h);
						BlueGoal = blue;
					}
				}
			}
			OpposingGoalColor = (GoalColor)Serial4.read();
		}
	}

	GoalData Yellow() const { return YellowGoal; }
	GoalData Blue() const { return BlueGoal; }
	GoalData OpposingGoal() const
	{
		if (OpposingGoalColor == GoalColor::None)
			nullptr;
		else if (OpposingGoalColor == GoalColor::Yellow)
			return YellowGoal;
		else if (OpposingGoalColor == GoalColor::Blue)
			return BlueGoal;
	}

	GoalColor OpposingColor() const { return OpposingGoalColor; }
private:
	GoalData YellowGoal;
	GoalData BlueGoal;
	GoalColor OpposingGoalColor = GoalColor::None;
};