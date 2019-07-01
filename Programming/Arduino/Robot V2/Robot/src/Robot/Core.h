#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include "Utils/Error.h"
#include "Utils/Timer.h"
#include "Utils/EventTimer.h"

#pragma region General

#define I2C_CONNECTION_TIMEOUT			1000

#define SENSOR_I2C_DELAY_MS			1
#define SENSOR_I2C_DELAY_MICRO		30

#define SENSOR_LIGHT_DATA_COUNT		8
#define SENSOR_TSOP_DATA_COUNT		8

#define DELAY_STATUS_LED_WAIT		1000
#define DELAY_STATUS_LED_ERROR		50
#define DELAY_STATUS_LED_DIAGNOSIS	200
#define DELAY_DIAGNOSTIC_SEND		100

#define MOTOR_1						0x00
#define MOTOR_2						0x01
#define MOTOR_3						0x02
#define MOTOR_4						0x03

#define MOTOR_DIR_FORWARD			0x01
#define MOTOR_DIR_REVERSE			0x00

#pragma endregion

#pragma region Commands

#define CMD_DIAGNOSTIC_START		0xA5
#define CMD_DIAGNOSTIC_STOP			0xA6
#define CMD_DIAGNOSTIC_I2C_SCAN		0xA7

#define CMD_MOVE					0x00
#define CMD_MOTOR_1					0x01
#define CMD_MOTOR_2					0x02
#define CMD_MOTOR_3					0x03
#define CMD_MOTOR_4					0x04
#define CMD_MOTOR_ALL				0x05
#define CMD_MOTOR_OFFSET			0x06
#define CMD_LIGHTGATE				0x07

#pragma endregion