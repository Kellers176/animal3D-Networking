#ifndef POWERPIPEVENT_H
#define POWERPIPEVENT_H

#include "A3_DEMO\a3_Event.h"
#include "A3_DEMO\a3_NetworkingManager.h"

class PowerPipEvent : public a3_Event
{
public:
	PowerPipEvent();
	PowerPipEvent(a3_NetworkingManager* net);
	~PowerPipEvent();
	void execute();
	void dispatch();


private:
	int iD;
	bool activated;
	a3_NetworkingManager* net;
};

#endif