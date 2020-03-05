

#ifndef MANAGERS_H
#define MANAGERS_H

#include "A3_DEMO/a3_EventManager.h"
#include "A3_DEMO/a3_NetworkingManager.h"
struct Managers
{
	a3_EventManager eventManager[1];
	a3_NetworkingManager net[1];
};


#endif