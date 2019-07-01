#pragma once

#include "../Core.h"

namespace Robot {
	
	class Device
	{
	public:
		Device()
			: m_Name(""), m_ID(m_PrevID++)
		{ }

		Device(const char* name)
			: m_Name(name), m_ID(m_PrevID++)
		{ }

		const char* GetName() const { return m_Name; }
		int GetID() const { return m_ID; }
	protected:
		const char* m_Name;
		const int m_ID;
	private:
		static int m_PrevID;
	};
}