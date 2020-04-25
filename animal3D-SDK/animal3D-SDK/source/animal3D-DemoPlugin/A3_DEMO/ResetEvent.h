#ifndef RESETEVENT_H
#define RESETEVENT_H

#include "A3_DEMO\a3_Event.h"
// #include "A3_DEMO/CookieClicker.h"
#include "A3_DEMO/a3_NetworkingManager.h"

class ResetEvent : public a3_Event
{

public:

	ResetEvent();
	ResetEvent(a3_NetworkingManager* net);
	~ResetEvent();
	void execute();
	void dispatch();

private:
	int iD;
	bool timeToReset;
	a3_NetworkingManager* net;
};

#endif