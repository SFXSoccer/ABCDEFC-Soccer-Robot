#pragma once

#ifndef _AVR_ATMEGA328PB_H_INCLUDED
#error "Wrong board selected for this program, please select an ATmega328PB"
#endif

#define NAME_CAPTAIN_AMERICA
//#define NAME_IRON_MAN
//#define NAME_THOR

#pragma region General

#ifdef NAME_CAPTAIN_AMERICA
	#define	ADDRESS			0x02
#elif defined NAME_IRON_MAN
	#define	ADDRESS			0x03
#elif defined NAME_THOR
	#define	ADDRESS			0x04
#endif

#define SENSOR_COUNT		8

#define SENSOR_1			0
#define SENSOR_2			1
#define SENSOR_3			2
#define SENSOR_4			3
#define SENSOR_5			4
#define SENSOR_6			5
#define SENSOR_7			6
#define SENSOR_8			7

#define IR_BACKGROUND		125

#pragma endregion

#pragma region Pins

#define LED_STATUS			LED_BUILTIN

#define PIN_POWER			7

#define PIN_SENSOR_1		A0
#define PIN_SENSOR_2		A1
#define PIN_SENSOR_3		A2
#define PIN_SENSOR_4		A3
#define PIN_SENSOR_5		A4
#define PIN_SENSOR_6		A5
#define PIN_SENSOR_7		A6
#define PIN_SENSOR_8		A7

#pragma endregion