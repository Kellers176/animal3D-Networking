#include "ResetEvent.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"

#include "A3_DEMO\ResetMessage.h"


enum a3_NetGameMessages
{
	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM,

	ID_GAME_MESSAGE_1 = 135,

	ID_ADD_INPUT = 136,
	ID_UPDATE_FOR_USER = 137,
	ID_ADD_EVENT = 138,
	//ID_UPDATE_OBJECT_POS = 139,
	ID_CREATE_USERS_OBJECT = 140,
	ID_CREATE_OWN_OBJECT = 141,
	ID_SEND_PIP_GAINED, // from player to server to other player
	ID_SEND_POWER_GAINED,
	ID_SEND_SCORE, // from server to the players
	ID_SEND_DIRECTION,

	ID_START_GAME,
	ID_PLAYER_DIED,

	ID_SET_ID,
	ID_RESET_POS
};


ResetEvent::ResetEvent()
{
	needToReset = false;
}

ResetEvent::ResetEvent(a3_NetworkingManager* mynet)
{
	needToReset = false;
	net = mynet;
}

ResetEvent::~ResetEvent()
{
}

void ResetEvent::execute()
{
	ResetMessage* message = new ResetMessage();
	message->typeID = ID_RESET_POS;
	message->resetMe = true;

	RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
	RakNet::SystemAddress* serverAddress = (RakNet::SystemAddress*)net->port_inbound;

	RakNet::BitStream bsOut[1];
	//rest of message
	bsOut->Write((RakNet::MessageID)ID_RESET_POS);
	bsOut->Write(message->resetMe);
	peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->serverAddress, false);
}

void ResetEvent::dispatch()
{
}


