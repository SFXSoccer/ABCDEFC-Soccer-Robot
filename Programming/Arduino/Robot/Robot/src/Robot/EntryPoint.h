#pragma once

extern Robot::Application* Robot::CreateApplication();
Robot::Application* App;

int _PrevStartRead = 0x0;
int _PrevStopRead = 0x0;
int _PrevCommStartRead = 0x0;
int _PrevCommStopRead = 0x0;

void setup()
{
	App = Robot::CreateApplication();
}

void loop()
{
	if (Robot::Error::GetStatus() != Robot::Error::FAILURE)
	{
		if (App->GetStartDevice().GetID() != App->GetStopDevice().GetID())
		{
			if (App->GetStartDevice().Read() != _PrevStartRead)
			{
				_PrevStartRead = App->GetStartDevice().Read();
				if (App->GetStartDevice().Read())
					App->Start();
			}
			else if (App->GetStopDevice().Read() != _PrevStopRead)
			{
				_PrevStopRead = App->GetStopDevice().Read();
				if (App->GetStopDevice().Read())
					App->Stop();
			}
		}
		else if (App->GetStartDevice().Read() != _PrevStartRead)
		{
			_PrevStartRead = App->GetStartDevice().Read();
			if (App->GetStartDevice().Read())
			{
				if (!App->IsRunning()) App->Start();
				else App->Stop();
			}
		}

		if (App->GetCommStartDevice().GetID() != App->GetCommStopDevice().GetID())
		{
			if (App->GetCommStartDevice().Read() != _PrevCommStartRead)
			{
				_PrevCommStartRead = App->GetCommStartDevice().Read();
				if (App->GetCommStartDevice().Read())
					App->GetCommDevice().Enable(true);
			}
			else if (App->GetCommStopDevice().Read() != _PrevCommStopRead)
			{
				_PrevCommStopRead = App->GetCommStopDevice().Read();
				if (App->GetCommStopDevice().Read())
					App->GetCommDevice().Enable(false);
			}
		}
		else if (App->GetCommStartDevice().Read() != _PrevCommStartRead)
		{
			_PrevCommStartRead = App->GetCommStartDevice().Read();
			if (App->GetCommStartDevice().Read())
				App->GetCommDevice().Enable(!App->GetCommDevice().Enabled());
		}

		if (App->IsRunning())
			App->Run();
	}
}