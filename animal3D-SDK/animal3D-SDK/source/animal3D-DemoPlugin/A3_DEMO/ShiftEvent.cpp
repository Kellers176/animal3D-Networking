#include "ShiftEvent.h"
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"

ShiftEvent::ShiftEvent()
{
	numToIncriment = 0;

}

ShiftEvent::ShiftEvent(a3_NetworkingManager* myNet, CookieClicker* cookie)
{
	myCookie = cookie;
	myCookie->number = cookie->number;
	numToIncriment = 0;
	net = myNet;
}

ShiftEvent::~ShiftEvent()
{
}

void ShiftEvent::execute()
{
	myCookie->number++;

	ShiftEvent myEvent;
	myEvent.iD = 139; //SentStruct
	myEvent.numToIncriment = myCookie->number;

	RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
	RakNet::SystemAddress* serverAddress = (RakNet::SystemAddress*)net->port_inbound;
	peer->Send(reinterpret_cast<char*>(&myEvent), sizeof(&myEvent), HIGH_PRIORITY, RELIABLE_ORDERED, 1, *serverAddress, true);
	//call network manager
}

void ShiftEvent::dispatch()
{

}
