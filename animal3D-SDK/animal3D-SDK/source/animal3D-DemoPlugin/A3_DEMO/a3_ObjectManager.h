

#ifndef A3_OBJECT_MANAGER_H
#define A3_OBJECT_MANAGER_H

#include <vector>
#include "a3_Object.h"

class a3_ObjectManager
{
public:
	a3_ObjectManager(){}
	~a3_ObjectManager(){}

	void a3_UpdateAllObjects(float deltaTime);
	void a3_RenderAllObjects(a3_TextRenderer* newRenderer);

	void a3_CreateNewObject();
	void a3_CreateNewObjectWithID(int userID, int newID);

	a3_Object* a3_GetObjectInPos(int objPos);
	a3_Object* a3_GetObjectFromID(int userID, int unitID);

	void a3_SetObjectPos(int userID, int objID, BK_Vector2 newPos);
	void a3_SetObjectVel(int userID, int objID, BK_Vector2 newPos);
	void a3_SetObjectRotation(int userID, int objID, float newRotation);

	int GetSize() { return (int)listOfObjects.size(); }

private:
	std::vector<a3_Object*> listOfObjects;
};

#endif