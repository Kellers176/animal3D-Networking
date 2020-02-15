#ifndef A3_NETWORKING_EVENT_H
#define A3_NETWORKING_EVENT_H

#include <string>
#include <iostream>
using namespace std;

//assign eventId to string
#define EVENTID string



class a3_Networking_Event
{
private:
	EVENTID eventId;
	

public:
	a3_Networking_Event(EVENTID myEventId)
	{
		this->eventId = myEventId;
	}

	~a3_Networking_Event();

	EVENTID getEventId() const { return eventId; }
	//as per dans request
//	virtual void execute() = 0;
//	virtual void dispatch() = 0;


};



#endif // !NETWORKING_EVENT
