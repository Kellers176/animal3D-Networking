

#include "a3_ObjectManager.h"
#include <iostream>
#include <fstream>
using namespace std;

void a3_ObjectManager::CreateLevel(std::string fileName)
{
	// variables used for reading in from the file
	ifstream fin;
	string line;

	int mWidth = 20;
	int mHeight = 23;

	// creates the strings for each header object based on the current level

	fin.open(fileName);

	if (fin.fail())
	{
		cout << "data retrieval process failed" << endl;
		return;
	}

	// obtains multiple variables from the data file
	while (!fin.eof())
	{
		char input;

		fin >> input;

		// creates the level layout based on the "image" in the file


			// create level layout

		int xPos = 1;
		int yPos = 1;
		int i = 0;

		// replace 300 with the actual size of the grid
		while(input != '$')
		{
			fin.get(input);

			

			/*

			Static objects:
			'#' - wall and cannot be cannot be moved onto
			'.' - pip and can be moved onto
			' ' - AKA space and can be moved onto
			'O' - is mega pip and can be moved onto and makes the text blue

			Dynamic:
			'@' - is pacman and will either be Green or (dark plain as day non pink) Purple

			'B' - is Blinky (will be red) ghost
			'I' - inky (will be cyan)
			'P' - pinky (will be pink)
			'C' - clyde (will be orange)

			*/

			//xPos = (xPos % (mWidth+1))+1;
			//yPos = (yPos % mHeight)+1;

			float frameWidth = 960;
			float frameHeight = 540;

			float realPosX = (16*xPos / frameWidth - 0.5f) * 2;
			float realPosY = -(18*yPos / frameHeight - 0.5f) * 2;

			if (input == '#')
			{
				a3byte* objectShape[1];
				objectShape[0] = "#";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), i, true, false, false);
			}
			else if (input == '.')
			{
				a3byte* objectShape[1];
				objectShape[0] = ".";


				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), i, true, true, false);
			}
			else if (input == ' ')
			{
				a3byte* objectShape[1];
				objectShape[0] = " ";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), i, true, false, false);
			}
			else if (input == 'O')
			{
				a3byte* objectShape[1];
				objectShape[0] = "O";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), i, true, true, false);
			}
			else if (input == '+')
			{
				a3byte* objectShape[1];
				objectShape[0] = ".";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), i, true, true, true);
			}
			else if (input == '-')
			{
				a3byte* objectShape[1];
				objectShape[0] = "-";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), i, true, false, false);
			}
			else if(input =='\n')
			{
				yPos++;
				xPos = 0;
				i--;
			}

			i++;
			xPos++;
			
			/*
			else if (input == 'B')
			{
				a3byte objectShape[1];
				objectShape[0] = 'B';

				a3_CreateNewObject(objectShape, BK_Vector2((float)xPos, (float)yPos));
			}
			else if (input == 'I')
			{
				a3byte objectShape[1];
				objectShape[0] = 'I';

				a3_CreateNewObject(objectShape, BK_Vector2((float)xPos, (float)yPos));
			}
			else if (input == 'P')
			{
				a3byte objectShape[1];
				objectShape[0] = 'P';

				a3_CreateNewObject(objectShape, BK_Vector2((float)xPos, (float)yPos));
			}
			else if (input == 'C')
			{
				a3byte objectShape[1];
				objectShape[0] = 'C';

				a3_CreateNewObject(objectShape, BK_Vector2((float)xPos, (float)yPos));
			}
			*/

			
		}

	}

	fin.clear();
	fin.close();

	// we have loaded the map and now we will spawn pacman
	a3byte* pacmanShape[1];
	pacmanShape[0] = "@";

	BK_Vector2 pacmanPos = BK_Vector2(listOfObjects[348]->getPosition().xVal, listOfObjects[348]->getPosition().yVal);

	a3_CreateNewDynamicObject(pacmanShape, pacmanPos, 348);

	// creating ghosts:
	a3byte* binkyShape[1];
	binkyShape[0] = "B";

	a3byte* pinkyShape[1];
	pinkyShape[0] = "P";

	a3byte* inkyShape[1];
	inkyShape[0] = "I";

	a3byte* clydeShape[1];
	clydeShape[0] = "C";

	int binkyNode = 188;
	int pinkyNode = 189;
	int inkyNode = 208;
	int clydeNode = 209;

	BK_Vector2 binkyPos = BK_Vector2(listOfObjects[binkyNode]->getPosition().xVal, listOfObjects[binkyNode]->getPosition().yVal);
	BK_Vector2 pinkyPos = BK_Vector2(listOfObjects[pinkyNode]->getPosition().xVal, listOfObjects[pinkyNode]->getPosition().yVal);
	BK_Vector2 inkyPos = BK_Vector2(listOfObjects[inkyNode]->getPosition().xVal, listOfObjects[inkyNode]->getPosition().yVal);
	BK_Vector2 clydePos = BK_Vector2(listOfObjects[clydeNode]->getPosition().xVal, listOfObjects[clydeNode]->getPosition().yVal);

	a3_CreateNewGhostObject(binkyShape, binkyPos, 186);
	a3_CreateNewGhostObject(pinkyShape, pinkyPos, 188);
	a3_CreateNewGhostObject(inkyShape, inkyPos, 206);
	a3_CreateNewGhostObject(clydeShape, clydePos, 208);
}

void a3_ObjectManager::a3_UpdateAllObjects(float deltaTime)
{
	ghostTimer += deltaTime;

	// updating the players' movement
	for (int i = 0; i < listOfDynamicObjects.size(); i++)
	{
		// pacman's movement:
		BK_Vector2 diff = listOfDynamicObjects[i]->getPosition() - listOfObjects[listOfDynamicObjects[i]->getCurrentNode()]->getPosition();
		if (diff.magnitude() <= 0.001f)
		{
			if (listOfObjects[listOfDynamicObjects[i]->getCurrentNode()]->getIsEdible())
			{
				a3byte* blankSpaceShape[1];
				blankSpaceShape[0] = " ";
				listOfObjects[listOfDynamicObjects[i]->getCurrentNode()]->changeObjectShape(blankSpaceShape);
			}

			bool isSameDirection = (playerInputDirection == listOfDynamicObjects[i]->getDirection());

			// change in direction

			if (!isSameDirection)
			{
				int playerDirection = listOfDynamicObjects[i]->getDirection();
				int oldCurrentNode = listOfDynamicObjects[i]->getCurrentNode();
				int newCurrentNode = listOfObjects[oldCurrentNode]->getConnections(playerInputDirection);

				if (listOfObjects[newCurrentNode]->getCanMoveToThisObject())
				{
					listOfDynamicObjects[i]->setDirection(playerInputDirection);
					listOfDynamicObjects[i]->setCurrentNode(newCurrentNode);
				}
				else
				{
					//playerInputDirection = listOfDynamicObjects[i]->getDirection();
					newCurrentNode = listOfDynamicObjects[i]->getDirection();
					listOfDynamicObjects[i]->setCurrentNode(listOfObjects[oldCurrentNode]->getConnections(newCurrentNode));

				}
			}
			else
			{
				int playerDirection = listOfDynamicObjects[i]->getDirection();
				int oldCurrentNode = listOfDynamicObjects[i]->getCurrentNode();
				int newCurrentNode = listOfObjects[oldCurrentNode]->getConnections(playerDirection);

				if (listOfObjects[newCurrentNode]->getCanMoveToThisObject())
				{
					//std::cout << "\nwe are going to next node\n";

					listOfDynamicObjects[i]->setCurrentNode(newCurrentNode);
				}
				else
				{
					//std::cout << "\nwe are stopping\n";

					listOfDynamicObjects[i]->setDirection(Direction::stop);
					listOfDynamicObjects[i]->setCurrentNode(oldCurrentNode);
				}
			}


		}
		
		listOfDynamicObjects[i]->a3_UpdateKinematics(deltaTime, listOfObjects[listOfDynamicObjects[i]->getCurrentNode()]->getPosition());
	}

	// updating the ghosts movement
	for (int i = 0; i < listOfGhostObjects.size(); i++)
	{
		if (ghostTimer > 8.0f)
		{
			if (!listOfGhostObjects[i]->getHasStartedMoving())
			{
				ghostTimer = 0;
				//std::cout << "\na ghost is spawning\n";
				int spawnNodePos = 148;
				BK_Vector2 ghostStart = BK_Vector2(listOfObjects[spawnNodePos]->getPosition().xVal, listOfObjects[spawnNodePos]->getPosition().yVal);
				listOfGhostObjects[i]->setObjectPos(ghostStart.xVal,ghostStart.yVal);
				listOfGhostObjects[i]->setHasStartMoving(true);
				listOfGhostObjects[i]->setDirection(Direction::left);
				listOfGhostObjects[i]->setCurrentNode(spawnNodePos);
			}
		}

		// their movement
		if (listOfGhostObjects[i]->getHasStartedMoving())
		{
			BK_Vector2 diff = listOfGhostObjects[i]->getPosition() - listOfObjects[listOfGhostObjects[i]->getCurrentNode()]->getPosition();
			if (diff.magnitude() <= 0.001f)
			{
				std::cout << "\nwe reached our goal baby\n";


				// change in direction
				if (listOfObjects[listOfGhostObjects[i]->getCurrentNode()]->getisTurnSpotObject())
				{
					Direction randomDir;

					bool validLocation = false;
					int playerDirection = listOfGhostObjects[i]->getDirection();
					int oldCurrentNode = listOfGhostObjects[i]->getCurrentNode();
					int newCurrentNode = -1;
					do 
					{
						randomDir = (Direction)(rand() % 4);

						playerDirection = listOfGhostObjects[i]->getDirection();
						oldCurrentNode = listOfGhostObjects[i]->getCurrentNode();
						newCurrentNode = listOfObjects[oldCurrentNode]->getConnections(randomDir);

						if (listOfObjects[newCurrentNode]->getCanMoveToThisObject())
						{
							switch (listOfGhostObjects[i]->getDirection())
							{
							case Direction::left:
								if (randomDir != Direction::right)
								{
									validLocation = true;
								}
								break;
							case Direction::down:
								if (randomDir != Direction::up)
								{
									validLocation = true;
								}
								break;
							case Direction::right:
								if (randomDir != Direction::left)
								{
									validLocation = true;
								}
								break;
							case Direction::up:
								if (randomDir != Direction::down)
								{
									validLocation = true;
								}
								break;
							default:
								break;
							}
						}
					} while (!validLocation);

					bool isSameDirection = (randomDir == listOfGhostObjects[i]->getDirection());

					if (!isSameDirection)
					{

						if (listOfObjects[newCurrentNode]->getCanMoveToThisObject())
						{
							listOfGhostObjects[i]->setDirection(randomDir);
							listOfGhostObjects[i]->setCurrentNode(newCurrentNode);
						}
						else
						{
							playerInputDirection = listOfGhostObjects[i]->getDirection();
							newCurrentNode = listOfObjects[oldCurrentNode]->getConnections(playerInputDirection);
							listOfGhostObjects[i]->setCurrentNode(newCurrentNode);

						}
					}
					else
					{
						if (listOfObjects[newCurrentNode]->getCanMoveToThisObject())
						{
							std::cout << "\nwe are going to next node\n";

							listOfGhostObjects[i]->setCurrentNode(newCurrentNode);
						}
						else
						{
							std::cout << "\nwe are stopping\n";

							listOfGhostObjects[i]->setDirection(Direction::stop);
							listOfGhostObjects[i]->setCurrentNode(oldCurrentNode);
						}
					}

				}
				else
				{
					int playerDirection = listOfGhostObjects[i]->getDirection();
					int oldCurrentNode = listOfGhostObjects[i]->getCurrentNode();
					int newCurrentNode = listOfObjects[oldCurrentNode]->getConnections(playerDirection);

					if (listOfObjects[newCurrentNode]->getCanMoveToThisObject())
					{
						std::cout << "\nwe are going to next node\n";

						listOfGhostObjects[i]->setCurrentNode(newCurrentNode);
					}
					else
					{
						std::cout << "\nwe are stopping\n";

						listOfGhostObjects[i]->setDirection(Direction::stop);
						newCurrentNode = listOfObjects[oldCurrentNode]->getConnections(playerDirection);
						listOfGhostObjects[i]->setCurrentNode(newCurrentNode);
					}
				}
			}
			listOfGhostObjects[i]->a3_UpdateKinematics(deltaTime, listOfObjects[listOfGhostObjects[i]->getCurrentNode()]->getPosition());
		}
	}




}

void a3_ObjectManager::a3_RenderAllObjects(a3_TextRenderer* newRenderer)
{
	if (listOfObjects.size() > 0)
	{
		for (int i = 0; i < listOfObjects.size(); i++)
		{
			listOfObjects[i]->a3_RenderObject(newRenderer);
		}
	}
	if (listOfDynamicObjects.size() > 0)
	{
		for (int i = 0; i < listOfDynamicObjects.size(); i++)
		{
			listOfDynamicObjects[i]->a3_RenderObject(newRenderer);
		}
	}
	if (listOfGhostObjects.size() > 0)
	{
		for (int i = 0; i < listOfGhostObjects.size(); i++)
		{
			listOfGhostObjects[i]->a3_RenderObject(newRenderer);
		}
	}
}

void a3_ObjectManager::a3_CreateNewObject(a3byte** newText, BK_Vector2 newPos, int posInArray,bool isStatic, bool canMoveToObject, bool isTurnSpot)
{
	a3_Object* newObject = new a3_Object(newText, newPos);

	newObject->setIsStaticObject(isStatic);

	newObject->setCanMoveToThisObject(canMoveToObject);

	newObject->setisTurnSpotObject(isTurnSpot);

	newObject->setConnections(posInArray);

	listOfObjects.push_back(newObject);
}

void a3_ObjectManager::a3_CreateNewDynamicObject(a3byte** newText, BK_Vector2 newPos,int currentNode)
{
	a3_Object* newObject = new a3_Object(newText, newPos);

	newObject->setIsStaticObject(false);
	newObject->setCurrentNode(currentNode);

	listOfDynamicObjects.push_back(newObject);
}

void a3_ObjectManager::a3_CreateNewGhostObject(a3byte** newText, BK_Vector2 newPos, int currentNode)
{
	a3_Object* newObject = new a3_Object(newText, newPos);

	newObject->setIsStaticObject(false);
	newObject->setCurrentNode(currentNode);
	newObject->setIsEdible(false);

	listOfGhostObjects.push_back(newObject);
}


void a3_ObjectManager::a3_CreateNewObjectWithID(int newID)
{
	a3byte* objectShape[1];
	objectShape[0] = "T";

	a3_Object* newObject = new a3_Object(objectShape, BK_Vector2(0,0));

	newObject->setObjectPos(0, 0);
	
	newObject->setObjectID(newID);

	listOfObjects.push_back(newObject);
}

a3_Object* a3_ObjectManager::a3_GetObjectInPos(int objPos)
{ 
	if (listOfObjects[objPos])
		return listOfObjects[objPos];
	else
		return nullptr;
}

a3_Object* a3_ObjectManager::a3_GetObjectFromID(int unitID)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i]->getObjectID() == unitID)
		{
			return listOfObjects[i];
		}
	}
	return nullptr;
}


//for all other objects that are not us, update Position
void a3_ObjectManager::a3_SetObjectPos(int objID, BK_Vector2 newPos)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i]->getObjectID() == objID)
		{
			listOfObjects[i]->setObjectPos(newPos.xVal, newPos.yVal);
		}
	}
}

void a3_ObjectManager::a3_SetObjectVel(int objID, BK_Vector2 newVel)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i]->getObjectID() == objID)
		{
			listOfObjects[i]->setObjectVelocity(newVel.xVal, newVel.yVal);
		}
	}
}

//for all other objects that are not us, update rotation
void a3_ObjectManager::a3_SetObjectRotation(int objID, float newRotation)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i]->getObjectID() == objID)
		{					
			listOfObjects[i]->setObjectRotation(newRotation);
		}
	}

}


