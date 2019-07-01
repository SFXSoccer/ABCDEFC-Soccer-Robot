//#define INIT_RUN				// Run after application is setup
//#define COMM_SERIAL_BAUD 9600	// Sets the communtication serial baud rate (default is 9600)

#include "Robot.h"

class SoccerRobot : public Robot::Application
{
public:
	SoccerRobot()
	{
		Serial.begin(9600);

		startButton = new Robot::DigitalDevice("StartButton", 35, INPUT);
		stopButton = new Robot::DigitalDevice("StopButton", 27, INPUT);
		startCommButton = new Robot::DigitalDevice("StartCommButton", 33, INPUT);
		stopCommButton = new Robot::DigitalDevice("StopCommButton", 37, INPUT);

		statusLed = new Robot::AnalogDevice("StatusLED", LED_BUILTIN);
		led = new Robot::DigitalDevice("LED", 30, OUTPUT);

		comm = new Robot::CommDevice("Comm", &Serial3);

		SetStartDevice(startButton);
		SetStopDevice(startButton);

		statusLed->Write(10);
	}

	~SoccerRobot()
	{ }

	void Begin() override
	{
		Robot::Error::Report(Robot::Error::NONE, "Just a test", statusLed->GetName(), statusLed->GetID());
		statusLed->Write(255);
		timer.Restart();
	}

	void End() override
	{
		statusLed->Write(10);

		led->Write(LOW);
	}

	void Run() override
	{
		if (timer > 1000)
		{
			if (timer < 1500) led->Write(HIGH);
			else if (timer < 2000) led->Write(LOW);
			else timer.Restart();
		}
	}

private:
	Robot::Timer timer;

	Robot::DigitalDevice* startButton;
	Robot::DigitalDevice* stopButton;

	Robot::DigitalDevice* startCommButton;
	Robot::DigitalDevice* stopCommButton;

	Robot::AnalogDevice* statusLed;
	Robot::DigitalDevice* led;

	Robot::CommDevice* comm;
};

Robot::Application* Robot::CreateApplication()
{
	return new SoccerRobot();
}