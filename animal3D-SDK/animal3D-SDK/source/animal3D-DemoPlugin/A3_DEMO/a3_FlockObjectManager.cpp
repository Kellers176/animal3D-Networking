
#include "FlockObjectManager.h"

void a3_FlockObjectManager::AddNewFlockObject(float positionX, float positionY, int unitID, bool controlledByUser)
{
	FlockObject newObject;
	newObject.SetPosition(positionX, positionY);
	newObject.SetUnitID(unitID);
	listOfFlockObjects.push_back(newObject);

	if (controlledByUser)
	{
		listOfControlledUnitIds.push_back(unitID);
	}
}

void a3_FlockObjectManager::UpdatePositionOfFlockObject(float newPosX, float newPosY, int unitID)
{
	for (int i = 0; i < listOfFlockObjects.size(); i++)
	{
		if (listOfFlockObjects[i].GetUnitID() == unitID)
		{
			listOfFlockObjects[i].SetPosition(newPosX, newPosY);
			break;
		}
	}
}


void a3_FlockObjectManager::UpdateAllFlockObjects(float deltaTime)
{
	for (int i = 0; i < listOfFlockObjects.size(); i++)
	{
		listOfFlockObjects[i].UpdateFlockObject(deltaTime);
	}
}

void a3_FlockObjectManager::UpdateOnlyUsersFlockObjects(float deltaTime)
{
	for (int k = 0; k < listOfControlledUnitIds.size(); k++)
	{
		GetFlockObject(listOfControlledUnitIds[k]).UpdateFlockObject(deltaTime);
	}
}

void a3_FlockObjectManager::RenderAllFlockObjects()
{
	for (int i = 0; i < listOfFlockObjects.size(); i++)
	{
		listOfFlockObjects[i].RenderObject();
	}
}
