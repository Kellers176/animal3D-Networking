
#include "a3_Networking_Listener.h"
#include "animal3D/a3input/a3_KeyboardInput.h"

#ifndef MOVE_INPUT_LISTENER_H
#define MOVE_INPUT_LISTENER_H

class MoveInputListener : public a3_Networking_Listener
{
public :
	MoveInputListener();
	MoveInputListener(a3_KeyboardKey newKey);
	~MoveInputListener();

	void SetListenerKey(a3_KeyboardKey newKey);

	void HandleEvent(a3_Networking_Event* event);

private:
	a3_KeyboardKey listernKey;
};

#endif