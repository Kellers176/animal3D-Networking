#include "a3_Networking_EventSystem.h"

a3_Networking_EventSystem::~a3_Networking_EventSystem()
{
	this->shutdown();
}

a3_Networking_EventSystem* a3_Networking_EventSystem::Instance()
{
	static a3_Networking_EventSystem instance;
	return &instance;
}

void a3_Networking_EventSystem::addEvent(EVENTID event, a3_Networking_Listener* listener)
{
	//if listener is null, already registered
	if (!listener || alreadyAdded(event, listener))
	{
		return;
	}
	//insert the new listener into the database
	data.insert(make_pair(event, listener));
}

void a3_Networking_EventSystem::deleteEvent(EVENTID event, a3_Networking_Listener* listener)
{
	//iter
	pair<multimap<EVENTID, a3_Networking_Listener*>::iterator,
		multimap<EVENTID, a3_Networking_Listener*>::iterator> range;

	//find all listeners able to recieve evvent
	range = data.equal_range(event);

	//for every listener who can respond to event
	for (multimap<EVENTID, a3_Networking_Listener*>::iterator iter = range.first; iter != range.second; iter++)
	{
		//if this is one to remove, we remove
		if ((*iter).second == listener)
		{
			//erase em
			iter = data.erase(iter);
			break;
		}
	}

}

//unregister listener from all events
void a3_Networking_EventSystem::deleteAllEvents(a3_Networking_Listener* listener)
{
	multimap<EVENTID, a3_Networking_Listener*>::iterator iter = data.begin();

	//for every entry in the data
	while (iter != data.end())
	{
		//if this is the one to delete
		if ((*iter).second == listener)
		{
			//destroy
			iter = data.erase(iter);
		}
		else
		{
			//move on
			iter++;
		}
	}


}

void a3_Networking_EventSystem::sendEvent(EVENTID eventId)
{
	//create the events
	a3_Networking_Event newEvent(eventId);
	//queue it 
	curEvents.push_back(newEvent);
}

void a3_Networking_EventSystem::processEvents()
{
	//for every event
	while (curEvents.size())
	{
		//dispatch the event
		dispatch(&curEvents.front());
		//remove the event
		curEvents.pop_front();
	}

}

void a3_Networking_EventSystem::clearEvents()
{
	//clear the events
	curEvents.clear();
}

void a3_Networking_EventSystem::shutdown()
{
	data.clear();
	curEvents.clear();

}
bool a3_Networking_EventSystem::alreadyAdded(EVENTID eventId, a3_Networking_Listener* listener)
{
	//34
	//assume they are not registered
	bool registered = false;

	//range iter
	pair<multimap<EVENTID, a3_Networking_Listener*>::iterator,
		multimap<EVENTID, a3_Networking_Listener*>::iterator> range;

	//find all listeners able to recieve evnet
	range = data.equal_range(eventId);

	//go through list of listeners
	for (multimap<EVENTID, a3_Networking_Listener*>::iterator iter = range.first; iter != range.second; iter++)
	{
		//if the listener is already subscribed
		if ((*iter).second == listener)
		{
			registered = true;
			break;
		}
	}

	return registered;
}

void a3_Networking_EventSystem::dispatch(a3_Networking_Event* event)
{
	//iterator
	pair< multimap<EVENTID, a3_Networking_Listener*>::iterator,
		multimap<EVENTID, a3_Networking_Listener*>::iterator> range;

	//go through users who respond to this event
	range = data.equal_range(event->getEventId());

	//go through list of listeners to respond to this
	for (multimap<EVENTID, a3_Networking_Listener*>::iterator iter = range.first; iter != range.second; iter++)
	{
		//handle the event
		(*iter).second->HandleEvent(event);
	}
}
