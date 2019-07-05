#pragma once

#ifndef _AVR_ATMEGA328PB_H_INCLUDED
#error "Wrong board selected for this program, please select an ATmega328PB"
#endif

//#define NAME_ANT_MAN
//#define NAME_BLACK_PANTHER
#define NAME_DOCTOR_STRANGE

#pragma region General

#ifdef NAME_ANT_MAN
	#define	ADDRESS					0x06
#elif defined NAME_BLACK_PANTHER
	#define	ADDRESS					0x07
#elif defined NAME_DOCTOR_STRANGE
	#define	ADDRESS					0x08
#endif

#define LIGHT_COLOR_WHITE_BUFFER	200

#define SENSOR_COUNT				8

#define SENSOR_1					0
#define SENSOR_2					1
#define SENSOR_3					2
#define SENSOR_4					3
#define SENSOR_5					4
#define SENSOR_6					5
#define SENSOR_7					6
#define SENSOR_8					7

#define CALIBRATION_COUNT			10

#pragma endregion

#pragma region Pins

#define LED_STATUS					LED_BUILTIN

#define PIN_SENSOR_1				A0
#define PIN_SENSOR_2				A1
#define PIN_SENSOR_3				A2
#define PIN_SENSOR_4				A3
#define PIN_SENSOR_5				A4
#define PIN_SENSOR_6				A5
#define PIN_SENSOR_7				A6
#define PIN_SENSOR_8				A7

#pragma endregion