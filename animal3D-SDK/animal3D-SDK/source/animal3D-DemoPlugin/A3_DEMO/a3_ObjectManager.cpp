

#include "a3_ObjectManager.h"


void a3_ObjectManager::a3_UpdateAllObjects(float deltaTime)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		listOfObjects[i].a3_UpdateKinematics(deltaTime);
	}
}

void a3_ObjectManager::a3_RenderAllObjects(a3_TextRenderer* newRenderer)
{
	if (listOfObjects.size() > 0)
	{
		for (int i = 0; i < listOfObjects.size(); i++)
		{
			listOfObjects[i].a3_RenderObject(newRenderer);
		}
	}
}

void a3_ObjectManager::a3_CreateNewObject()
{
	a3_Object newObject = a3_Object();

	newObject.setObjectPos(0, 0);

	listOfObjects.push_back(newObject);
}

void a3_ObjectManager::a3_CreateNewObjectWithID(int newID)
{
	a3_Object newObject = a3_Object();

	newObject.setObjectPos(0, 0);
	
	newObject.setObjectID(newID);

	listOfObjects.push_back(newObject);
}

//for all other objects that are not us, update Position
void a3_ObjectManager::a3_SetObjectPos(int objID, BK_Vector2 newPos)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i].getObjectID() == objID)
		{
			listOfObjects[i].setObjectPos(newPos.xVal, newPos.yVal);
		}
	}
}

void a3_ObjectManager::a3_SetObjectVel(int objID, BK_Vector2 newVel)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i].getObjectID() == objID)
		{
			listOfObjects[i].setObjectVelocity(newVel.xVal, newVel.yVal);
		}
	}
}

//for all other objects that are not us, update rotation
void a3_ObjectManager::a3_SetObjectRotation(int objID, float newRotation)
{
	for (int i = 0; i < listOfObjects.size(); i++)
	{
		if (listOfObjects[i].getObjectID() == objID)
		{
			listOfObjects[i].setObjectRotation(newRotation);
		}
	}

}


