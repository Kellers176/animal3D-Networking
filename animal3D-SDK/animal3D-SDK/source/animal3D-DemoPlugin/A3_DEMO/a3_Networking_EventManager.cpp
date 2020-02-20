#include "a3_Networking_EventManager.h"

a3_Networking_EventSystem::a3_Networking_EventSystem()
{
}

a3_Networking_EventSystem::~a3_Networking_EventSystem()
{
}

a3_Networking_EventSystem* a3_Networking_EventSystem::Instance()
{
	static a3_Networking_EventSystem instance;
	return &instance;
}

void a3_Networking_EventSystem::addEvent(a3_Networking_Event* myEvent)
{
	curEvents.push_back(myEvent);
}

void a3_Networking_EventSystem::deleteEvent(a3_Networking_Event* myEvent)
{
	for (int i = 0; i < curEvents.size(); i++)
	{
		if (curEvents.at(i) == myEvent)
		{
			curEvents.erase(curEvents.begin() + i);
		}
	}
}

void a3_Networking_EventSystem::processEvents()
{
	for (int i = 0; i < curEvents.size(); i++)
	{
		curEvents.at(i)->execute();
	}
}
