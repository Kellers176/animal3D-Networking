#ifndef SHIFTEVENT_H
#define SHIFTEVENT_H

#include "A3_DEMO/a3_Networking_Event.h"

class ShiftEvent : a3_Networking_Event
{

public:

	ShiftEvent();
	~ShiftEvent();
	void execute();
	void dispatch();

private:
	int numToIncrment;

};

#endif