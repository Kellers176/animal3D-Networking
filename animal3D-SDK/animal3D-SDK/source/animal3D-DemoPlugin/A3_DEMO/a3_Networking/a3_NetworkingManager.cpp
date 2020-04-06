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
#include <string>

//-----------------------------------------------------------------------------
// networking stuff

enum a3_NetGameMessages
{
	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM,

	ID_GAME_MESSAGE_1 = 135,

	ID_ADD_INPUT = 136,
	ID_UPDATE_FOR_USER = 137,
	ID_ADD_EVENT = 138,

	ID_UPDATE_OBJECT_POS = 139,
	ID_CREATE_USERS_OBJECT = 140,
	ID_CREATE_OWN_OBJECT = 141,


	ID_RECEIVE_PUSH_DATA = 142,
	ID_RECEIVE_SHARE_DATA = 143,
	ID_RECEIVE_COUPLING_DATA = 144,
	ID_RECEIVE_SERVER_TYPE = 145
};

// data share, data push, data coupling

// data share comes from people to server to other people
// data push comes from server to the people
// data coupling comes from people to server calculates more and then push to other

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

a3i32 a3netNetworkingLoop(a3_NetworkingManager* net, a3_ObjectManager& newObjMan, float deltaTime)
{
	
	// this is wrong atm
	//make own send function to send the stuff
	// for (int i = 0; i < 16; i++)
	// {
	// 	net->participants[i].timeSinceLastPing = net->participants[i].timeSinceLastPing + deltaTime;
	// 
	// 	if (net->participants[i].timeSinceLastPing > 3.0f)
	// 	{
	// 		Participant temp = net->participants[i];
	// 		newObjMan.a3_SetObjectPos(net->userID,temp.ID, temp.lastPos + (temp.lastVel * deltaTime));
	// 		net->participants[i].lastPos = temp.lastPos + (temp.lastVel * deltaTime);
	// 	}
	// }


	return 0;
}


// connect
a3i32 a3netConnect(a3_NetworkingManager* net, a3netAddressStr const ip)
{
	if (net && net->peer)
	{
		RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
		//RakNet::ConnectionAttemptResult connectionRes;
		//connectionRes = peer->Connect(ip, net->port_outbound, 0, 0);
		peer->Connect(ip, net->port_outbound, 0, 0);
		/*
		if (connectionRes == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED)
		{
			printf("connection attempt started");
		}
		else if (connectionRes == RakNet::ConnectionAttemptResult::ALREADY_CONNECTED_TO_ENDPOINT)
		{
			printf("already connected to endpoint");
		}
		else if (connectionRes == RakNet::ConnectionAttemptResult::CANNOT_RESOLVE_DOMAIN_NAME)
		{
			printf("cannot resolve domain name");
		}
		else if (connectionRes == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_ALREADY_IN_PROGRESS)
		{
			printf("connection attempt already in progress");
		}
		else if (connectionRes == RakNet::ConnectionAttemptResult::INVALID_PARAMETER)
		{
			printf("invalid parameter");
		}
		else if (connectionRes == RakNet::ConnectionAttemptResult::SECURITY_INITIALIZATION_FAILED)
		{
			printf("security initialization failed");
		}
		*/
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
a3i32 a3netProcessInbound(a3_NetworkingManager* net, a3_ObjectManager& newObjMan)
{
	if (net && net->peer)
	{
		RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;
		RakNet::Packet* packet;
		RakNet::MessageID msg;
		a3i32 count = 0;

		for (packet = peer->Receive();
			packet;
			peer->DeallocatePacket(packet), packet = peer->Receive(), ++count)
		{
			RakNet::BitStream bs_in(packet->data, packet->length, false);
			bs_in.Read(msg);

			switch (msg)
			{
				// check for timestamp and process
			case ID_TIMESTAMP:
			{
				bs_in.Read(msg);
				// ****TO-DO: handle timestamp
				RakNet::Time sendTime, recieveTime, dt;
				bs_in.Read(sendTime);
				recieveTime = RakNet::GetTime();
				dt = recieveTime - sendTime;
				printf("\n SEND TIME: %u \n", (unsigned int)sendTime);
				printf("\n RECIEVE TIME: %u \n", (unsigned int)recieveTime);
				printf("\n DIFF TIME: %u \n", (unsigned int)dt);
			}
				// do not break; proceed to default case to process actual message contents
			default:
			{

				printf("\nThere is no timestamp!!!\n");
				switch (msg)
				{
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				{
					printf("\nAnother client has disconnected.\n");
					break;
				}
				case ID_REMOTE_CONNECTION_LOST:
				{
					printf("\nAnother client has lost the connection.\n");
					net->numberOfParticipants = net->numberOfParticipants - 1;
					break;
				}
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
				{
					printf("\nAnother client has connected.\n");
					net->participants[net->numberOfParticipants].ID = net->numberOfParticipants;
					net->participants[net->numberOfParticipants].lastPos = BK_Vector2(0, 0);
					net->participants[net->numberOfParticipants].lastVel = BK_Vector2(0, 0);
					net->participants[net->numberOfParticipants].timeSinceLastPing = 0;
					net->numberOfParticipants = net->numberOfParticipants + 1;
					break;
				}
				case ID_CONNECTION_REQUEST_ACCEPTED:
				{
					printf("\nOur connection request has been accepted.\n");
					{
						net->serverAddress = packet->systemAddress;


						// read in the users id
						//bs_in.Read(net->userID);

						/*
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

						*/

					}
					break;
				}
				case ID_NEW_INCOMING_CONNECTION:
				{
					// we add number of participants...
					printf("\nA connection is incoming.\n");

					RakNet::BitStream bsInitialDataOut[1];
					bsInitialDataOut->Write((RakNet::MessageID)ID_RECEIVE_SERVER_TYPE);
					bsInitialDataOut->Write(net->shareType);
					peer->Send(bsInitialDataOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);


					RakNet::BitStream bsOut[1];

					// make the person create their object
					bsOut->Write((RakNet::MessageID)ID_CREATE_OWN_OBJECT);
					bsOut->Write(net->numberOfParticipants);

					peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

					// create an object with the id we sent them...
					int tempID = net->numberOfParticipants;

					newObjMan.a3_CreateNewObjectWithID(net->userID, tempID);

					// tell the new guy make objects for the other people
					RakNet::BitStream bsToNewUserOut[1];
					
					if (net->numberOfParticipants > 0)
					{
						for (int i = 0; i < net->numberOfParticipants; i++)
						{
							bsToNewUserOut->Write((RakNet::MessageID)ID_CREATE_USERS_OBJECT);
							bsToNewUserOut->Write(i);

							peer->Send(bsToNewUserOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
						}
					}

					RakNet::BitStream bsToOthersOut[1];
					// tell the previous people to make a new person
					if (net->numberOfParticipants > 0)
					{
						for (int i = 0; i < net->numberOfParticipants; i++)
						{
							bsToOthersOut->Write((RakNet::MessageID)ID_CREATE_USERS_OBJECT);
							bsToOthersOut->Write(net->numberOfParticipants);

							peer->Send(bsToOthersOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->peer->GetSystemAddressFromIndex(i), false);
						}
					}

					net->numberOfParticipants = net->numberOfParticipants + 1;

					net->userID = -1;

					break;
				}
				case ID_NO_FREE_INCOMING_CONNECTIONS:
				{
					printf("\nThe server is full.\n");
					break;
				}
				case ID_DISCONNECTION_NOTIFICATION:
				{
					if (net->maxConnect_outbound) {
						printf("\nA client has disconnected.\n");
					}
					else {
						printf("\nWe have been disconnected.\n");
					}
					break;
				}
				case ID_CONNECTION_LOST:
				{
					if (net->maxConnect_outbound) {
						printf("\nA client lost the connection.\n");
					}
					else {
						printf("\nConnection lost.\n");
					}
					break;
				}
				case ID_GAME_MESSAGE_1:
				{
					printf("\nDEBUG MESSAGE: received packet ID_GAME_MESSAGE_1.\n");
					{
						RakNet::RakString rs;
						bs_in.Read(rs);
						printf("%s\n", rs.C_String());

						// get the input


					}
					break;
				}
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

				case ID_UPDATE_OBJECT_POS:
				{
					int unitsID = -1;
					bs_in.Read(unitsID);

					printf("\nupdating pos of" + unitsID);

					float newPosX, newPosY, newVelX, newVelY;

					bs_in.Read(newPosX);
					bs_in.Read(newPosY);
					bs_in.Read(newVelX);
					bs_in.Read(newVelY);

					if (unitsID != net->userID)
					{
						newObjMan.a3_SetObjectPos(net->userID, unitsID, BK_Vector2(newPosX, newPosY));
						newObjMan.a3_SetObjectVel(net->userID, unitsID, BK_Vector2(newVelX, newVelY));
					}

					for (int i = 0; i < 16; i++)
					{
						if (net->participants[i].ID == unitsID)
						{
							net->participants[i].timeSinceLastPing = 0;
						}
					}

					break;
				}
				case ID_CREATE_USERS_OBJECT:
				{
					printf("\ncreating a new unit\n");
					int usersID = -1;

					bs_in.Read(usersID);

					for (int i = 0; i < 10; i++)
					{
						newObjMan.a3_CreateNewObjectWithID(usersID,i);
					}

					break;
				}
				case ID_CREATE_OWN_OBJECT:
				{
					printf("\ncreating a new unit\n");
					int usersID = -1;

					bs_in.Read(usersID);
					net->userID = usersID;

					for (int i = 0; i < 10; i++)
					{
						newObjMan.a3_CreateNewObjectWithID(net->userID, i);
					}

					break;
				}
				case ID_RECEIVE_PUSH_DATA:
				{
					// received by the clients from teh server always
					int userID = -1;
					int unitID = -1;

					// get the user that is updating
					bs_in.Read(userID);
					// get uniot of that user
					bs_in.Read(unitID);

					float newPosX, newPosY, newVelX, newVelY;

					bs_in.Read(newPosX);
					bs_in.Read(newPosY);
					bs_in.Read(newVelX);
					bs_in.Read(newVelY);

					break;
				}
				case ID_RECEIVE_SHARE_DATA:
				{
					// check if server or not
					if (net->isServer)
					{
						// get the user that is updating
						int userID = -1;
						bs_in.Read(userID);

						int unitID = -1;


						// get unit of that user
						bs_in.Read(unitID);

						float newPosX, newPosY, newVelX, newVelY;

						bs_in.Read(newPosX);
						bs_in.Read(newPosY);
						bs_in.Read(newVelX);
						bs_in.Read(newVelY);

						RakNet::BitStream bsOut[1];

						bsOut->Write((RakNet::MessageID)ID_RECEIVE_COUPLING_DATA);

						bsOut->Write(userID);
						bsOut->Write(unitID);

						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getPosition().xVal);
						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getPosition().yVal);
						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getVelocity().xVal);
						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getVelocity().yVal);

						if (net->numberOfParticipants > 1)
						{
							for (int i = 0; i < net->numberOfParticipants; i++)
							{
								peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->peer->GetSystemAddressFromIndex(i), false);
							}
						}

					}
					else
					{
						// if client then update stuff if its not your stuff

						// get the user that is updating
						int userID = -1;
						bs_in.Read(userID);

						if (userID != net->userID)
						{
							int unitID = -1;


							// get uniot of that user
							bs_in.Read(unitID);

							float newPosX, newPosY, newVelX, newVelY;

							bs_in.Read(newPosX);
							bs_in.Read(newPosY);
							bs_in.Read(newVelX);
							bs_in.Read(newVelY);
						}

					}

					break;
				}
				case ID_RECEIVE_COUPLING_DATA:
				{
					RakNet::Time sendTime, recieveTime, dt;
					bs_in.Read(sendTime);
					recieveTime = RakNet::GetTime();
					dt = recieveTime - sendTime;
					printf("\n SEND TIME: %u \n", (unsigned int)sendTime);
					printf("\n RECIEVE TIME: %u \n", (unsigned int)recieveTime);
					printf("\n DIFF TIME: %u \n", (unsigned int)dt); 

					// get the user that is updating
					int userID = -1;
					bs_in.Read(userID);

					int unitID = -1;


					// get uniot of that user
					bs_in.Read(unitID);

					float newPosX, newPosY, newVelX, newVelY;

					bs_in.Read(newPosX);
					bs_in.Read(newPosY);
					bs_in.Read(newVelX);
					bs_in.Read(newVelY);

					newObjMan.a3_SetObjectPos(userID, unitID, BK_Vector2(newPosX, newPosY));

					newObjMan.a3_GetObjectFromID(userID, unitID)->a3_UpdateSteering(dt);

					if (net->isServer)
					{	
						RakNet::BitStream bsOut[1];

						bsOut->Write((RakNet::MessageID)ID_RECEIVE_COUPLING_DATA);

						bsOut->Write(RakNet::GetTime());

						bsOut->Write(userID);
						bsOut->Write(unitID);

						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getPosition().xVal);
						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getPosition().yVal);
						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getVelocity().xVal);
						bsOut->Write(newObjMan.a3_GetObjectFromID(userID, unitID)->getVelocity().yVal);

						if (net->numberOfParticipants > 1)
						{
							for (int i = 0; i < net->numberOfParticipants; i++)
							{
								peer->Send(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->peer->GetSystemAddressFromIndex(i), false);
							}
						}
					}

					break;
				}
				case ID_RECEIVE_SERVER_TYPE:
				{
					ServerShareType tempType;
					bs_in.Read(tempType);

					if (tempType == 0 || tempType == 1 || tempType == 2)
					{
						net->shareType = tempType;
					}
					break;
				}
				default:
				{
					printf("\nMessage with identifier %i has arrived.\n", msg);
					break;
				}
				}
				break;
			}
			}
		}
		return count;
	}
	return 0;
}

// process outbound packets
a3i32 a3netProcessOutbound(a3_NetworkingManager* net, a3_ObjectManager& newObjMan)
{
	
	RakNet::RakPeerInterface* peer = (RakNet::RakPeerInterface*)net->peer;

	if (net && net->peer)
	{
		if (net->isServer)
		{
			switch (net->shareType)
			{
			case push:
			{
				// send all that shit my way bebe
				break;
			}
			case share:
			{
				//  we dont do anything because when we receive the data from the user
				// we do stuff then send it through the inbound
				break;
			}
			case coupling:
			{
				// we dont do anything because when we receive the data from the user
				// we do stuff then send it through the inbound 
				break;
			}
			default:
				break;
			}
		}
		else
		{
			switch (net->shareType)
			{
			case push:
			{
				// do nothing we are only receiving 
				break;
			}
			case share:
			{
				// send it
				break;
			}
			case coupling:
			{
				// send it
				break;
			}
			default:
				break;
			}
		}
	}

	//RakNet::BitStream bsOut[1];
	/*
	if (net && net->peer)
	{
		if (net->isServer)
		{
			// sending to everyone:
			for (unsigned int i = 0; i < net->peer->GetNumberOfAddresses(); i++)
			{
				for (int j = 0; j < newObjMan.GetSize(); j++)
				{
					RakNet::BitStream bsServerOut[1];

					// we need the id and the position and the velocity
					bsServerOut->Write((RakNet::MessageID)ID_UPDATE_OBJECT_POS);

					// newObjMan.a3_GetObjectInPos(j);

					bsServerOut->Write(newObjMan.a3_GetObjectInPos(j)->getObjectID());
					bsServerOut->Write(newObjMan.a3_GetObjectInPos(j)->getPosition().xVal);
					bsServerOut->Write(newObjMan.a3_GetObjectInPos(j)->getPosition().yVal);
					bsServerOut->Write(newObjMan.a3_GetObjectInPos(j)->getVelocity().xVal);
					bsServerOut->Write(newObjMan.a3_GetObjectInPos(j)->getVelocity().yVal);

					net->peer->Send(bsServerOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->serverAddress, true);

				}

			}

		}
		else
		{
			a3_Object* temp = newObjMan.a3_GetObjectFromID(net->userID);

			if (temp)
			{
				RakNet::BitStream bsClientOut[1];

				// we need the id and the position and the velocity
				bsClientOut->Write((RakNet::MessageID)ID_UPDATE_OBJECT_POS);
				bsClientOut->Write(newObjMan.a3_GetObjectFromID(net->userID)->getObjectID());
				bsClientOut->Write(newObjMan.a3_GetObjectFromID(net->userID)->getPosition().xVal);
				bsClientOut->Write(newObjMan.a3_GetObjectFromID(net->userID)->getPosition().yVal);
				bsClientOut->Write(newObjMan.a3_GetObjectFromID(net->userID)->getVelocity().xVal);
				bsClientOut->Write(newObjMan.a3_GetObjectFromID(net->userID)->getVelocity().yVal);

				//sending to server
				net->peer->Send(bsClientOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, net->serverAddress, false);
			}

		}

	}
	*/
	return 0;
}


//-----------------------------------------------------------------------------
