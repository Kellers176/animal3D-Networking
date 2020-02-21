#ifndef SHIFTEVENT_H
#define SHIFTEVENT_H

#include "a3_Event.h"

class ShiftEvent : public a3_Event
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