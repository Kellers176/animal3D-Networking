#include "Something.h"

Something::Something(int yesPlz)
{
	myVar = yesPlz;
}

void Something::HandleEvent(a3_Networking_Event* event)
{
	myVar = 5;
	otherStuff = 6;

	//in main:
	/*
	Something bob(7);
	Something bill(9);

	a3_Networking_EventSystem::Instance()->addEvent("ColorMeMine", &bob);
	a3_Networking_EventSystem::Instance()->addEvent("ColorPixel", &bill);
	a3_Networking_EventSystem::Instance()->addEvent("DoNothing", &bob);
	a3_Networking_EventSystem::Instance()->addEvent("DoNothing", &bill);
	
	//process events
	a3_Networking_EventSystem::Instance()->ProcessEvents();

	//listen for thingss
	if(input->keypressed(SDLK_f))
	{
		a3_Networking_EventSystem::Instance()->SendEvent("ColorMeMine", /*1);
	}

	a3_Networking_EventSystem::Instance()->Shutdown();
	
	*/
	

}
