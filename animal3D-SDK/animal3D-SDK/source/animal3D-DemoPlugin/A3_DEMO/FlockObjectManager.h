


#ifndef  A3_FLOCK_OBJECT_MANAGER_H
#define  A3_FLOCK_OBJECT_MANAGER_H

#include "a3_FlockObject.h"
#include <vector>

class a3_FlockObjectManager
{
public:
	a3_FlockObjectManager(){}
	~a3_FlockObjectManager(){}

	void AddNewFlockObject(float positionX, float positionY, int unitID, bool controlledByUser);

	void UpdateAllFlockObjects(float deltaTime);

	void UpdateOnlyUsersFlockObjects(float deltaTime);

	void RenderAllFlockObjects();

	FlockObject GetFlockObject(int unitID) { return listOfFlockObjects[unitID]; }

private:
	std::vector<FlockObject> listOfFlockObjects;
	std::vector<int> listOfControlledUnitIds;
};

#endif // ! A3_FLOCK_OBJECT_MANAGER_H
