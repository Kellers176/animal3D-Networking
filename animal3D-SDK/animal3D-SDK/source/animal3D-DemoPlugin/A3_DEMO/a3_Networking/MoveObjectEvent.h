

#include "a3_Networking_Event.h"
#include "A3_DEMO/a3_DemoState.h"

#ifndef MOVE_OBJ_H
#define MOVE_OBJ_H

class MoveObjectEvent : public a3_Networking_Event
{
public:

private:

	// need demo state ref for obj
	a3_DemoState* demoStateRef;

	// need movement up down left right

};

#endif