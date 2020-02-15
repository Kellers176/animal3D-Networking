#ifndef A3_NETWORKING_LISTENER_H
#define A3_NETWORKING_LISTENER_H

#include "a3_Networking_Event.h"

class a3_Networking_Listener
{
public:
	a3_Networking_Listener() {}
	virtual ~a3_Networking_Listener() {}

	virtual void HandleEvent(a3_Networking_Event* event) = 0;

};


#endif