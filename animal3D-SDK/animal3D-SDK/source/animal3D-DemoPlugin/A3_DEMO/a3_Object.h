

#ifndef A3_OBJECT_H
#define A3_OBJECT_H

#include "animal3D-A3DG/a3graphics/a3_TextRenderer.h"
#include "a3_ObjectKinematic.h"
#include <string>

enum Direction
{
	left = 0,
	down = 1, 
	right = 2,
	up = 3,
	stop = 4
};

class a3_Object
{
public:
	a3_Object(a3byte** newText, BK_Vector2 newPos);
	~a3_Object();

	void setConnections(int objectNodePos);
	int getConnections(int connectionDirection) { return connectionPos[connectionDirection]; }

	void a3_RenderObject(a3_TextRenderer* newRenderer);

	void a3_UpdateKinematics(float deltaTime, BK_Vector2 nodePos);

	void setObjectPos(float newX, float newY) { objectKinematic.position = BK_Vector2(newX, newY); }
	void setObjectVelocity(float newVelX, float newVelY) { objectKinematic.velocity = BK_Vector2(newVelX, newVelY); }
	void setObjectRotation(float newRotation) { objectKinematic.rotation = newRotation; }
	void setObjectID(int newID) { objectID = newID; }

	int getObjectID() { return objectID; }
	BK_Vector2 getPosition() { return objectKinematic.position; }
	BK_Vector2 getVelocity() { return objectKinematic.velocity; }

	void setIsStaticObject(bool newBool) { isStaticObject = newBool; }
	bool getIsStaticObject() { return isStaticObject; }

	void setCanMoveToThisObject(bool newBool) { canMoveToThisObject = newBool; }
	bool getCanMoveToThisObject() { return canMoveToThisObject; }	
	
	void setisTurnSpotObject(bool newBool) { isTurnSpot = newBool; }
	bool getisTurnSpotObject() { return isTurnSpot; }

	void setCurrentNode(int newNode) { currentNode = newNode; }
	int getCurrentNode() { return currentNode; }

	void setDirection(Direction newDirection) { movement = newDirection; }
	Direction getDirection() { return movement; }

	void setHasStartMoving(bool newBool) { hasStartedMoving = newBool; }
	bool getHasStartedMoving() { return hasStartedMoving; }

	void setIsEdible(bool newBool) { isEdible = newBool; }
	bool getIsEdible() { return isEdible; }

	void setIsPowerPip(bool newBool) { isPowerPip = newBool; }
	bool getIsPowerPip() { return isPowerPip; }

	void changeObjectShape(a3byte** newText) { objectShape[0] = newText[0];}
	std::string getObjectShape() { return objectShape[0]; }
private:
	const a3byte* objectShape[1];

	a3_Object_Kinematic objectKinematic;

	int objectID;

	bool isStaticObject = true;
	bool canMoveToThisObject = false;
	bool isTurnSpot = false;

	std::vector<int> connectionPos;

	Direction movement;
	int currentNode;

	bool hasStartedMoving = false;

	bool isEdible = true;
	bool isPowerPip = false;
};


#endif // A3_OBJECT_H
