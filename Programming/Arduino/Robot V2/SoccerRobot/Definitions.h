#pragma once

#pragma region General

#define SERIAL_BAUD_RATE				57600

#define DELAY_POWERUP					2000
#define I2C_CONNECTION_TIMEOUT			1000

#define SENSOR_TSOP_COUNT				24
#define SENSOR_LIGHT_COUNT				24

#define ADDR_SENSOR_TSOP_ARRAY_1		0x02
#define ADDR_SENSOR_TSOP_ARRAY_2		0x03
#define ADDR_SENSOR_TSOP_ARRAY_3		0x04

#define ADDR_SENSOR_LIGHTGATE			0x05
#define ADDR_MOTORCONTROLLER			0x05

#define ADDR_SENSOR_LIGHT_ARRAY_1		0x06
#define ADDR_SENSOR_LIGHT_ARRAY_2		0x07
#define ADDR_SENSOR_LIGHT_ARRAY_3		0x08

#pragma endregion

#pragma region Pins

#define LED_STATUS						LED_BUILTIN

#define PIN_BUTTON_0					24
#define PIN_BUTTON_1					25
#define PIN_BUTTON_2					26
#define PIN_BUTTON_3					27

#pragma endregion