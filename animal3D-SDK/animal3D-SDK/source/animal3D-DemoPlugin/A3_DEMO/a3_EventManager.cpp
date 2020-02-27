#include "a3_EventManager.h"

a3_EventManager::a3_EventManager()
{
}

a3_EventManager::~a3_EventManager()
{
}

a3_EventManager* a3_EventManager::Instance()
{
	static a3_EventManager instance;
	return &instance;
}

void a3_EventManager::addEvent(a3_Event* myEvent)
{
	curEvents.push_back(myEvent);
}

void a3_EventManager::deleteEvent(a3_Event* myEvent)
{
	for (int i = 0; i < curEvents.size(); i++)
	{
		if (curEvents.at(i) == myEvent)
		{
			curEvents.erase(curEvents.begin() + i);
		}
	}
}

void a3_EventManager::deleteAllEvents()
{
	for (int i = 0; i < curEvents.size(); i++)
	{
		curEvents.erase(curEvents.begin() + i);
	}
}

void a3_EventManager::processEvents()
{
	for (int i = 0; i < curEvents.size(); i++)
	{
		curEvents.at(i)->execute();
	}
	deleteAllEvents();

}
