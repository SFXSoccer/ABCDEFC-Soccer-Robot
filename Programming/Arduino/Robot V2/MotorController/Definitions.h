#pragma once

#ifndef _AVR_ATMEGA328PB_H_INCLUDED
#error "Wrong board selected for this program, please select an ATmega328PB"
#endif

#define GUARDIANS_OF_THE_GALAXY

#pragma region General

#ifdef GUARDIANS_OF_THE_GALAXY
#define	ADDRESS					0x05
#endif

#define DELAY_LIGHTGATE			0
#define DELAY_BALL_DETECTED		500

#define DIR_FORWARD				0x1
#define DIR_REVERSE				0x0

#define MOTOR_1_ANGLE			30
#define MOTOR_2_ANGLE			150
#define MOTOR_3_ANGLE			270
#define MOTOR_4_ANGLE			0

#pragma endregion

#pragma region Commands

#define CMD_MOTOR				0x15
#define CMD_LIGHTGATE			0x16

#pragma endregion

#pragma region Pins

#define LED_STATUS				LED_BUILTIN

#define PIN_LIGHTGATE_PWR		19
#define PIN_LIGHTGATE			A4

#define PIN_MOTOR_1_SPEED		9
#define PIN_MOTOR_1_DIRECTION	15
#define PIN_MOTOR_1_BRAKE		14

#define PIN_MOTOR_2_SPEED		10
#define PIN_MOTOR_2_DIRECTION	17
#define PIN_MOTOR_2_BRAKE		16

#define PIN_MOTOR_3_SPEED		11
#define PIN_MOTOR_3_DIRECTION	13
#define PIN_MOTOR_3_BRAKE		12

#define PIN_MOTOR_4_SPEED		3
#define PIN_MOTOR_4_DIRECTION	4
#define PIN_MOTOR_4_BRAKE		2
#pragma endregion