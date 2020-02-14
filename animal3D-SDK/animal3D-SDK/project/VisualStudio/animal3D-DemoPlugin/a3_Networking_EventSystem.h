#ifndef A3_NETWORKING_EVENTSYSTEM_H
#define A3_NETWORKING_EVENTSYSTEM_H

#include <list>
#include <map>

using namespace std;


#include "a3_Networking_Event.h"
#include "a3_Networking_Listener.h"

//this will be a singleton
class a3_Networking_EventSystem
{
private:
	//database of clients and their events
	multimap <EVENTID, a3_Networking_Listener*> data;

	//events to be processed
	list <a3_Networking_Event> curEvents;

	//helpers
	bool alreadyAdded(EVENTID eventID, a3_Networking_Listener* listener);
	void dispatch(a3_Networking_Event* event);


	//Singleton, deny access to constructors/ destructors
	a3_Networking_EventSystem() {};
	~a3_Networking_EventSystem();
	a3_Networking_EventSystem(const a3_Networking_EventSystem& rhs) {};
	a3_Networking_EventSystem& operator=(const a3_Networking_EventSystem& rhs) {};

public:
	//returns event system instance
	static a3_Networking_EventSystem* Instance();

	//registers a listener to start listening to an event
	void addEvent(EVENTID event, a3_Networking_Listener* listener);
	
	//unregisters a listener from a specific events
	void deleteEvent(EVENTID event, a3_Networking_Listener* listener);

	//delete listener from all events
	void deleteAllEvents(a3_Networking_Listener* listener);

	//send an event
	void sendEvent(EVENTID eventId/* Needss something else in this to send? void* something */);

	//process all events
	void processEvents();

	//clear the events
	void clearEvents();

	//shutdown the event system
	void shutdown();

};




#endif // !EVENT_SYSTEM_H

