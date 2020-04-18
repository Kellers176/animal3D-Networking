

#include "a3_ObjectManager.h"
#include <iostream>
#include <fstream>
using namespace std;

void a3_ObjectManager::CreateLevel(std::string fileName)
{
	// variables used for reading in from the file
	ifstream fin;
	string line;

	int mWidth = 39;
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

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), true, false,false);
			}
			else if (input == '.')
			{
				a3byte* objectShape[1];
				objectShape[0] = ".";


				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), true, true,false);
			}
			else if (input == ' ')
			{
				a3byte* objectShape[1];
				objectShape[0] = " ";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), true, false,false);
			}
			else if (input == 'O')
			{
				a3byte* objectShape[1];
				objectShape[0] = "O";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), true, true,false);
			}
			else if (input == '+')
			{
				a3byte* objectShape[1];
				objectShape[0] = ".";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), true, true,true);
			}
			else if (input == '-')
			{
				a3byte* objectShape[1];
				objectShape[0] = "-";

				a3_CreateNewObject(objectShape, BK_Vector2(realPosX, realPosY), true, false, false);
			}
			else if(input =='\n')
			{
				yPos++;
				xPos = 0;
			}

			xPos++;

			/*
			else if (input == '@')
			{
				a3byte objectShape[1];
				objectShape[0] = '@';

				a3_CreateNewObject(objectShape, BK_Vector2((float)xPos, (float)yPos),false,false);
			}
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
}

void a3_ObjectManager::a3_UpdateAllObjects(float deltaTime)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		listOfObjects[i]->a3_UpdateKinematics(deltaTime);
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
}

void a3_ObjectManager::a3_CreateNewObject(a3byte** newText, BK_Vector2 newPos, bool isStatic, bool canMoveToObject, bool isTurnSpot)
{
	a3_Object* newObject = new a3_Object(newText, newPos);

	newObject->setIsStaticObject(isStatic);

	newObject->setCanMoveToThisObject(canMoveToObject);

	newObject->setisTurnSpotObject(isTurnSpot);

	listOfObjects.push_back(newObject);
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


