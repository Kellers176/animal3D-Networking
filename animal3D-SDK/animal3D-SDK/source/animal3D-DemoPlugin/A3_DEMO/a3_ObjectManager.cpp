

#include "a3_ObjectManager.h"


void a3_ObjectManager::a3_UpdateAllObjects()
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		listOfObjects[i].a3_UpdateKinematics();
	}
}

void a3_ObjectManager::a3_RenderAllObjects()
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		listOfObjects[i].a3_RenderObject();
	}
}

void a3_ObjectManager::a3_CreateNewObject()
{
	a3_Object newObject = a3_Object();

	newObject.setObjectPos(0, 0);

	listOfObjects.push_back(newObject);
}

void a3_ObjectManager::a3_SetObjectPos(int objID, BK_Vector2 newPos)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i].getObjectID() == objID)
		{

		}
	}
}


