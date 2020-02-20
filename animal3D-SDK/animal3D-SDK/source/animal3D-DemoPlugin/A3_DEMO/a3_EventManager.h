#ifndef A3_EVENTMANAGER_H
#define A3_EVENTMANAGER_H


//using namespace std;
#include <vector>
#include "a3_Event.h"

class a3_EventManager
{
private:
	a3_EventManager();
	~a3_EventManager();
	std::vector<a3_Event*> curEvents;

public:

	static a3_EventManager* Instance();

	void addEvent(a3_Event* myEvent);
	void deleteEvent(a3_Event* myEvent);
	void processEvents();

	


};



#endif // ! a3_NETWORKING_EVENTMANAGER_H