
#include "a3_Networking_Listener.h"
#ifndef MOVE_INPUT_LISTENER_H
#define MOVE_INPUT_LISTENER_H

class MoveInputListener : public a3_Networking_Listener
{
public :
	MoveInputListener(){}
	MoveInputListener(a3_KeyboardKey newKey){ listernKey = newKey; }
	~MoveInputListener(){}

	void SetListenerLKey(a3_KeyboardKey newKey) { listernKey = newKey; }

private:
	a3_KeyboardKey listernKey;
};

#endif