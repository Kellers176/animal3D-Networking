#include "ShiftEvent.h"
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"

#include "A3_DEMO/CookieClicker.h"

enum a3_NetGameMessages
{
	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM,

	ID_GAME_MESSAGE_1,
	ID_ADD_INPUT,
	ID_UPDATE_FOR_USER,
	ID_ADD_EVENT,
	ID_SEND_STRUCT,
	ID_RECEIVE_STRUCT
};

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
	iDontNeedThis->typeID = ID_SEND_STRUCT;
	iDontNeedThis->number = 0;




	RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
	RakNet::SystemAddress* serverAddress = (RakNet::SystemAddress*)net->port_inbound;

	RakNet::BitStream bsOut[1];
	//rest of message
	bsOut->Write((RakNet::MessageID)ID_SEND_STRUCT);
	bsOut->Write(iDontNeedThis->number);
	peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->serverAddress, false);




	// peer->Send((const char*)(&iDontNeedThis), sizeof(&iDontNeedThis), HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->serverAddress, false);
	//call network manager

}

void ShiftEvent::dispatch()
{

}
