/*
	Copyright 2011-2020 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_NetworkingManager.cpp
	RakNet networking wrapper.
*/


#include "../a3_NetworkingManager.h"
#include "A3_DEMO/a3_EventManager.h"

#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"

#include "a3_Networking_ObjectInfo.h"

#include "A3_DEMO/CookieClicker.h"


//-----------------------------------------------------------------------------
// networking stuff

enum a3_NetGameMessages
{
	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM,

	ID_GAME_MESSAGE_1,

	ID_ADD_INPUT,
	ID_UPDATE_FOR_USER,
	ID_ADD_EVENT,
	ID_SEND_STRUCT,
	ID_RECEIVE_STRUCT,
	ID_ADD_INPUT_TO_GAME_OBJECT,
	ID_UPDATE_OBJECT_FOR_USER,
	ID_RECEIVE_DATA_SHARING_TYPE
};


#pragma pack(push, 1)

struct a3_NetGameMessageData
{
	unsigned char typeID;

	// ****TO-DO: implement game message data struct
	a3_KeyboardKey temp;

};

#pragma pack (pop)


// startup networking
a3i32 a3netStartup(a3_NetworkingManager* net, a3ui16 port_inbound, a3ui16 port_outbound, a3ui16 maxConnect_inbound, a3ui16 maxConnect_outbound)
{
	if (net && !net->peer)
	{
		RakNet::RakPeerInterface* peer = RakNet::RakPeerInterface::GetInstance();
		if (peer)
		{
			RakNet::SocketDescriptor socket[2] = {
				RakNet::SocketDescriptor(port_inbound, 0),		// server settings
				RakNet::SocketDescriptor(),//port_outbound, 0),	// client settings
			};

			// choose startup settings based on 
			a3boolean const isServer = port_inbound && maxConnect_inbound;
			a3boolean const isClient = port_outbound && maxConnect_outbound;
			if (peer->Startup(maxConnect_inbound + maxConnect_outbound, socket + isClient, isServer + isClient) == RakNet::StartupResult::RAKNET_STARTED)
			{
				peer->SetMaximumIncomingConnections(maxConnect_inbound);
				peer->SetOccasionalPing(true);

				net->port_inbound = port_inbound;
				net->port_outbound = port_outbound;
				net->maxConnect_inbound = maxConnect_inbound;
				net->maxConnect_outbound = maxConnect_outbound;
				net->peer = peer;

				return 1;
			}
		}
	}
	return 0;
}

// shutdown networking
a3i32 a3netShutdown(a3_NetworkingManager* net)
{
	if (net && net->peer)
	{
		RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
		RakNet::RakPeerInterface::DestroyInstance(peer);
		net->peer = 0;
		return 1;
	}
	return 0;
}

a3i32 a3netNetworkingLoop(a3_NetworkingManager* net)
{
	//make own send function to send the stuff
	return 0;
}


// connect
a3i32 a3netConnect(a3_NetworkingManager* net, a3netAddressStr const ip)
{
	if (net && net->peer)
	{
		RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
		peer->Connect(ip, net->port_outbound, 0, 0);
		return 1;
	}
	return 0;
}

// disconnect
a3i32 a3netDisconnect(a3_NetworkingManager* net)
{
	if (net && net->peer)
	{
		RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
		a3ui16 i, j = peer->NumberOfConnections();
		for (i = 0; i < j; ++i)
			peer->CloseConnection(peer->GetSystemAddressFromIndex(i), true);
		return 1;
	}
	return 0;
}


// process inbound packets
a3i32 a3netProcessInbound(a3_NetworkingManager* net)
{
	if (net && net->peer)
	{
		RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
		RakNet::Packet* packet;
		RakNet::MessageID msg;
		a3i32 count = 0;

		MoveInputData* tempInputData;
		ObjectPosInfo* tempMoveObjInfo;

		for (packet = peer->Receive();
			packet;
			peer->DeallocatePacket(packet), packet = peer->Receive(), ++count)
		{
			RakNet::BitStream bs_in(packet->data, packet->length, false);
			bs_in.Read(msg);

			RakNet::BitStream bs_Data_Out[1];

			switch (msg)
			{
				// check for timestamp and process
			case ID_TIMESTAMP:
				bs_in.Read(msg);
				// ****TO-DO: handle timestamp
				RakNet::Time sendTime, recieveTime, dt;
				bs_in.Read(sendTime);
				recieveTime = RakNet::GetTime();
				dt = recieveTime - sendTime;
				printf("\n SEND TIME: %u \n", (unsigned int)sendTime);
				printf("\n RECIEVE TIME: %u \n", (unsigned int)recieveTime);
				printf("\n DIFF TIME: %u \n", (unsigned int)dt);

				// do not break; proceed to default case to process actual message contents
			default:
				switch (msg)
				{
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
					printf("Another client has disconnected.\n");
					break;
				case ID_REMOTE_CONNECTION_LOST:
					printf("Another client has lost the connection.\n");
					net->numberOfParticipants = net->numberOfParticipants - 1;
					break;
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
					printf("Another client has connected.\n");
					net->numberOfParticipants = net->numberOfParticipants + 1;
					break;
				case ID_CONNECTION_REQUEST_ACCEPTED:
					printf("Our connection request has been accepted.\n");
					{
						net->serverAddress = packet->systemAddress;

						// Use a BitStream to write a custom user message
						// Bitstreams are easier to use than sending casted structures, 
						//	and handle endian swapping automatically
						RakNet::BitStream bsOut[1];
						RakNet::Time sendTime;
						//indicate timestamp intent
						bsOut->Write((RakNet::MessageID)ID_TIMESTAMP);
						//get time
						sendTime = RakNet::GetTime();
						bsOut->Write(RakNet::GetTime());
						//rest of message
						bsOut->Write((RakNet::MessageID)ID_GAME_MESSAGE_1);

						peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
						// ****TO-DO: write timestamped message
						printf("\n SEND TIME: %u \n", (unsigned int)sendTime);

						

					}
					break;
				case ID_NEW_INCOMING_CONNECTION:
					printf("A connection is incoming.\n");
					net->numberOfParticipants = net->numberOfParticipants + 1;

					bs_Data_Out->Write((RakNet::MessageID)ID_RECEIVE_DATA_SHARING_TYPE);
					bs_Data_Out->Write((TypeOfDataSharing)net->dataShareType);
					
					peer->Send(bs_Data_Out, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					printf("The server is full.\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					if (net->maxConnect_outbound) {
						printf("A client has disconnected.\n");
					}
					else {
						printf("We have been disconnected.\n");
					}
					break;
				case ID_CONNECTION_LOST:
					if (net->maxConnect_outbound) {
						printf("A client lost the connection.\n");
					}
					else {
						printf("Connection lost.\n");
					}
					break;

				case ID_GAME_MESSAGE_1:
					printf("DEBUG MESSAGE: received packet ID_GAME_MESSAGE_1.\n");
					{
						RakNet::RakString rs;
						bs_in.Read(rs);
						printf("%s\n", rs.C_String());

						// get the input


					}
					break;
				case ID_ADD_INPUT_TO_GAME_OBJECT:

					// server gets the input
					tempInputData = (MoveInputData*)packet->data;


					// event system will process it and return the new pos info


					break;
				case ID_UPDATE_OBJECT_FOR_USER:

					// get the infor from the server for the new move info
					tempMoveObjInfo = (ObjectPosInfo*)packet->data;

					// set the object pos to pos + move input


				case ID_ADD_EVENT:
				{
					//tell the client to process the envents
					//send a bool over to tell them to process events?
					//How would I send over the process events to the clients
					//a3_EventManager::Instance()->processEvents();
					//ShiftEvent* shift_Event = new ShiftEvent(&myCookie);
					//ShiftEvent* shift_Event = new ShiftEvent();
					//a3_EventManager::Instance()->addEvent(shift_Event);
					break;
				}
				case ID_SEND_STRUCT:
				{
					// get the message (this is automatically done)
					printf("we have received a message about le cookie uh huh huh huh\n");
					// increase the number
					net->CookieNumber = net->CookieNumber + 1;

					// transfer the data to a temporary container
					CookieClicker* myCookie = new CookieClicker();
					myCookie->typeID = ID_RECEIVE_STRUCT;
					myCookie->number = net->CookieNumber;

					int actualCookieNumber = myCookie->number;

					// send the temporary container out to everyone
					RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;

					RakNet::BitStream bsOut[1];
					//rest of message
					bsOut->Write((RakNet::MessageID)ID_RECEIVE_STRUCT);
					bsOut->Write(actualCookieNumber);

					for (int i = 0; i < net->numberOfParticipants; i++)
					{
						peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, peer->GetSystemAddressFromIndex(i), false);
					}

					break;
				}
				case ID_RECEIVE_STRUCT:
				{
					printf("\n mmmmmm cookie received\n");

					int actual = 0;

					// receive the new cookie amount from the server
					bs_in.Read(actual);

					// set the number of cookies to the number from the container from the server
					net->CookieNumber = actual;



					break;
				}

				case ID_RECEIVE_DATA_SHARING_TYPE:

					bs_in.Read(net->dataShareType);

					break;

				default:
					printf("Message with identifier %i has arrived.\n", msg);
					break;
				}
				break;
			}
		}
		return count;
	}
	return 0;
}

// process outbound packets
a3i32 a3netProcessOutbound(a3_NetworkingManager* net)
{
	if (net && net->peer)
	{
		if (net->isServer)
		{
			RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;

			RakNet::BitStream bsOut[1];

			/*
				unsigned char typeId;
				int objType;
				float xPos;
				float yPos;
				float zPos;
			*/

			ObjectPosInfo posData = ObjectPosInfo();
			posData.typeId = ID_UPDATE_OBJECT_FOR_USER;

			bsOut->Write((ObjectPosInfo)posData);

			for (unsigned int i = 0; i < peer->GetNumberOfAddresses(); i++)
			{
				peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, peer->GetSystemAddressFromIndex(i), false);
			}
		}
		else
		{
			RakNet::BitStream bsOut[1];
			
			MoveInputData moveInput = MoveInputData();
			moveInput.typeId = ID_ADD_INPUT_TO_GAME_OBJECT;

			bsOut->Write((MoveInputData)moveInput);
		}
	}
	return 0;
}


//-----------------------------------------------------------------------------
