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

	bool Detected()
	{
		return CenterX != CAMERA_GOAL_NOT_FOUND && CenterY != CAMERA_GOAL_NOT_FOUND &&
			Width != CAMERA_GOAL_NOT_FOUND && Height != CAMERA_GOAL_NOT_FOUND;
	}
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
				uint8_t goalColor = Serial4.read();
				m_OpposingGoalColor = goalColor == 0x01 ? GoalColor::Yellow : goalColor == 0x02 ? GoalColor::Blue : GoalColor::None;
			}
		}
	}

	GoalData Yellow() const { return YellowGoal; }
	GoalData Blue() const { return BlueGoal; }

	GoalData OpposingGoal() const
	{
		Serial.println(m_OpposingGoalColor);
		if (m_OpposingGoalColor == GoalColor::None)
			nullptr;
		else if (m_OpposingGoalColor == GoalColor::Yellow)
			return YellowGoal;
		else if (m_OpposingGoalColor == GoalColor::Blue)
			return BlueGoal;
	}

	GoalData FriendlyGoal() const
	{
		if (m_OpposingGoalColor == GoalColor::None)
			nullptr;
		else if (m_OpposingGoalColor == GoalColor::Yellow)
			return BlueGoal;
		else if (m_OpposingGoalColor == GoalColor::Blue)
			return YellowGoal;
	}

	GoalColor OpposingColor() const { return m_OpposingGoalColor; }
private:
	GoalData YellowGoal;
	GoalData BlueGoal;
	GoalColor m_OpposingGoalColor = GoalColor::None;
};