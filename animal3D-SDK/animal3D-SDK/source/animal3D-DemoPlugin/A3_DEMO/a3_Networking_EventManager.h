#ifndef  a3_NETWORKING_EVENTMANAGER_H
#define A3_NETWORKING_EVENTMANAGER_H

#include <vector>

using namespace std;

#include "a3_Networking_Event.h"

class a3_Networking_EventSystem
{
public:
	a3_Networking_EventSystem();
	~a3_Networking_EventSystem();

private:
	
	static a3_Networking_EventSystem* Instance();

	void addEvent(a3_Networking_Event* myEvent);
	void deleteEvent(a3_Networking_Event* myEvent);
	void processEvents();

	vector<a3_Networking_Event*> curEvents;


};



#endif // ! a3_NETWORKING_EVENTMANAGER_H
