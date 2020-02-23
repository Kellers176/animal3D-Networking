#ifndef SHIFTEVENT_H
#define SHIFTEVENT_H

#include "a3_Event.h"
#include "A3_DEMO/CookieClicker.h"

class ShiftEvent : public a3_Event
{

public:

	ShiftEvent();
	ShiftEvent(CookieClicker* cookie);
	~ShiftEvent();
	void execute();
	void dispatch();

private:
	int numToIncriment;
	CookieClicker* myCookie;
};

#endif