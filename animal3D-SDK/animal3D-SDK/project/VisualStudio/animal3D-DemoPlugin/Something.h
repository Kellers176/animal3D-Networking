#include "a3_Networking_Listener.h"
#include "a3_Networking_Event.h"

class Something : public a3_Networking_Listener
{
private:
	int myVar;
	int otherStuff;

public:
	Something(int yesPlz);
	void HandleEvent(a3_Networking_Event* event);
};