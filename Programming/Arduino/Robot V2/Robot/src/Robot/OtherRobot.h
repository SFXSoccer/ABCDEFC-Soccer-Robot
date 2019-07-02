#pragma once

enum PlayMode
{
	Undecided, Attacker, Defender
};

struct OtherRobot
{
	PlayMode Mode = PlayMode::Undecided;
	bool HasBall = false;
	bool Playing = false;
	uint8_t IRDirection = -1;
};