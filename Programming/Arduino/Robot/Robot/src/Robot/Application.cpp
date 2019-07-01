#include "Application.h"

namespace Robot {

	void Application::Start()
	{
		m_Running = true;
		Begin();
	}

	void Application::Stop()
	{
		m_Running = false;
		End();
	}
}