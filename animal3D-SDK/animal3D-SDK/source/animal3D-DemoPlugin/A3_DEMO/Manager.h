

#ifndef MANAGERS_H
#define MANAGERS_H

#include "A3_DEMO/CookieClicker.h"
#include "A3_DEMO/a3_EventManager.h"
#include "A3_DEMO/a3_NetworkingManager.h"
#include "A3_DEMO/FlockObjectManager.h"
struct Managers
{
	a3_EventManager eventManager[1];
	CookieClicker myCookie[1];
	a3_NetworkingManager net[1];
	
	a3_FlockObjectManager flockManager[1];
};


#endif