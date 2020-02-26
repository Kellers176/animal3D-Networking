#include "ShiftEvent.h"
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"

#include "A3_DEMO/CookieClicker.h"

ShiftEvent::ShiftEvent()
{
	numToIncriment = 0;

}

ShiftEvent::ShiftEvent(a3_NetworkingManager* myNet)
{
	numToIncriment = 0;
	net = myNet;
}

ShiftEvent::~ShiftEvent()
{
}

void ShiftEvent::execute()
{
	//myCookie->number++;

	// for this event we can literally just send something over with the ID:
	// ID_SEND_STRUCT (139)
	// and it will take care of everything for us




	CookieClicker* iDontNeedThis = new CookieClicker();
	iDontNeedThis->ID = 139;
	iDontNeedThis->number = 0;

	RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
	RakNet::SystemAddress* serverAddress = (RakNet::SystemAddress*)net->port_inbound;
	peer->Send(reinterpret_cast<char*>(&iDontNeedThis), sizeof(&iDontNeedThis), HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->serverAddress, false);
	//call network manager

}

void ShiftEvent::dispatch()
{

}
