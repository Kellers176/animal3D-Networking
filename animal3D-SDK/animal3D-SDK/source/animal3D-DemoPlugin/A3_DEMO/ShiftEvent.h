#ifndef SHIFTEVENT_H
#define SHIFTEVENT_H

#include "a3_Event.h"
#include "A3_DEMO/CookieClicker.h"
#include "A3_DEMO/a3_NetworkingManager.h"

class ShiftEvent : public a3_Event
{

public:

	ShiftEvent();
	ShiftEvent(a3_NetworkingManager* net, CookieClicker* cookie);
	~ShiftEvent();
	void execute();
	void dispatch();

private:
	int iD;
	int numToIncriment;
	CookieClicker* myCookie;
	a3_NetworkingManager* net;
};

#endif