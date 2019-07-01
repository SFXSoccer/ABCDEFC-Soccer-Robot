#pragma once

bool m_Running = false;

DigitalLED* StatusLED;
EventTimer m_StatusLEDBlink(1000);
EventTimer m_DiagnosticSendData(DELAY_DIAGNOSTIC_SEND);

Button* ButtonStart;
Button* ButtonStop;

void StartProgram()
{
	m_Running = true;

	StatusLED->Write(LOW);
	Begin();
}

void StopProgram()
{
	m_Running = false;

	StatusLED->Write(HIGH);
	End();
}

void ToggleStatusLED()
{
	*StatusLED = StatusLED->IsOn() ? LOW : HIGH;
}

void setup()
{
	m_StatusLEDBlink.SetElapsedEvent(&ToggleStatusLED);
	m_DiagnosticSendData.SetElapsedEvent(&Diagnostic::SendData);

	Init();

#ifdef INIT_RUN
	m_Running = true;
	Begin();
#endif
}

int data = 0;
void loop()
{
	while (Serial.available())
	{
		uint8_t data[1];
		data[0] = (uint8_t)Serial.read();
		Diagnostic::ReadData(data);
	}

	if (!Diagnostic::Running())
	{
		if (Error::GetStatus() != Error::FAILURE)
		{
			ButtonStart->Read();
			Update();

			if (m_Running)
				Run();
			else
			{
				m_StatusLEDBlink.SetInterval(DELAY_STATUS_LED_WAIT);
				m_StatusLEDBlink.Update();
			}
		}
		else
		{
			m_StatusLEDBlink.SetInterval(DELAY_STATUS_LED_ERROR);
			m_StatusLEDBlink.Update();
		}
	}
	else
	{
		Update();
		if (m_Running == true)
			StopProgram();

		m_DiagnosticSendData.Update();
		m_StatusLEDBlink.SetInterval(DELAY_STATUS_LED_DIAGNOSIS);
		m_StatusLEDBlink.Update();
	}
}