#pragma once
#include "Robot.h"

#include "LightSensorController.h"
#include "IRSensorController.h"
#include "Koala.h"

Accelerometer* Accel;
Camera* Cam;
Communication* XBee;
IRSensorController* IRSensors;
Lightgate* LightgateSensor;
LightSensorController* LightSensors;
Magnetometer* Compass;
MotorController* Motors;

Button* ButtomComms;

Koala* DropBear;

#ifdef ROBOT_ATTACK
PlayMode mode = PlayMode::Attacker;
#else
PlayMode mode = PlayMode::Defender;
#endif
OtherRobot Friendly;

#ifdef SHOW_UPS
uint32_t __Updates = 0;
Timer __UPS_Counter;
#endif

void ToggleProgram()
{
	if (m_Running)
	{
		StopProgram();
		Motors->SetOffset(0);
		Motors->Rotate(0);
	}
	else
		StartProgram();
}

void ToggleComms()
{

}

void Init()
{
	Serial.begin(57600);

	Diagnostic::SetConnectedDevice(0, true);

	StatusLED = new DigitalLED("LED_Status", LED_STATUS);

	DropBear = new Koala("Koala", PIN_KOALA_FADE, PIN_KOALA_BLINK);

	Serial.println("Waiting for complete system powerup...");
	delay(DELAY_POWERUP);
	Serial.println("Initializing devices...");

	ButtonStart = new Button("StartButton", PIN_BUTTON_3);
	ButtonStart->SetPressedEvent(&ToggleProgram);

	ButtomComms = new Button("CommButton", PIN_BUTTON_2);
	ButtomComms->SetPressedEvent(&ToggleComms);

	XBee = new Communication("Xbee");
	Cam = new Camera("Camera");

	Accel = new Accelerometer("Accelerometer", LSM303_ADDRESS_ACCEL);
	IRSensors = new IRSensorController("IRSensors");
	LightgateSensor = new Lightgate("Lightgate", ADDR_SENSOR_LIGHTGATE);
	LightSensors = new LightSensorController("LightSensors");
	Compass = new Magnetometer("Compass", LSM303_ADDRESS_MAG);
	Motors = new MotorController("Motors", ADDR_MOTORCONTROLLER);
	
	Serial.println("Initialzed devices, verifying connections...");

	bool lightGateConnection = LightgateSensor->VerifyConnection();
	bool motorControllerConnection = Motors->VerifyConnection();
	bool lightSensorConnection = LightSensors->VerifyConnections();
	bool IRSensorConnection = IRSensors->VerifyConnections();

	Diagnostic::SetConnectedDevice(4, lightGateConnection & motorControllerConnection);

	if (Error::GetStatus() == Error::ErrorStatus::FAILURE)
	{
		Serial.println("Verification connections failed!");
		return;
	}
	Serial.println("Verification connections completed");

	StatusLED->Write(HIGH);
}

void Update()
{
	Compass->Update();
	//Accel->Update();
	LightgateSensor->Update();
	LightSensors->Update();
	IRSensors->Update();
	Motors->Update();
	Cam->Update();

	DropBear->Update();

	uint8_t data[5] = { (int)mode, LightgateSensor->GetValue(), m_Running, IRSensors->Direction() };
	XBee->Update(&Friendly, data);

#ifdef SHOW_UPS
	__Updates++;

	if (__UPS_Counter > 1000)
	{
		Serial.print(__Updates);
		Serial.println(" Updates/s");
		__Updates = 0;
		__UPS_Counter.Restart();
	}
#endif
}
