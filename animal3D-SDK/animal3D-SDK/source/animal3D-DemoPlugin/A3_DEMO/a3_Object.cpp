#include "a3_Object.h"
#include <GL/glew.h>

#include <iostream>
#include <string>
a3_Object::a3_Object(a3byte** newText, BK_Vector2 newPos)
{
	//set default position
	objectKinematic = a3_Object_Kinematic();

	objectKinematic.position.xVal = newPos.xVal;
	objectKinematic.position.yVal = newPos.yVal;
	
	//create shape
	objectShape[0] = newText[0];

	objectID = -1;

	movement = left;

	//currentNode = -1;

	objectColor.r = 1;
	objectColor.g = 1;
	objectColor.b = 0;
	objectColor.a = 1;

}

a3_Object::~a3_Object()
{
	//unloads the text

}

void a3_Object::setConnections(int objectNodePos)
{
	// left
	if ((objectNodePos - 1) >= 0)
	{
		connectionPos.push_back((objectNodePos - 1));
	}
	// down
	if ((objectNodePos + 20) <= 460)
	{
		connectionPos.push_back((objectNodePos + 20));

	}
	//right
	if ((objectNodePos + 1) <= 460)
	{
		connectionPos.push_back((objectNodePos + 1));
	}
	// up
	if ((objectNodePos - 20) >= 0)
	{
		connectionPos.push_back((objectNodePos - 20));
	}
	// stop
	connectionPos.push_back(objectNodePos);
}


void a3_Object::a3_RenderObject(a3_TextRenderer* newRenderer)
{
	//-1,-1,-1 is bottom left corner
	//draw text
	a3textDraw(newRenderer, objectKinematic.position.xVal, objectKinematic.position.yVal, 0.0f, objectColor.r, objectColor.g, objectColor.b, 1.0f, objectShape[0]);
}


void a3_Object::a3_UpdateKinematics(float deltaTime, BK_Vector2 nodePos)
{
	float movementSpeedX = 0.04f;
	float movementSpeedY = 0.08f;

	BK_Vector2 playerMove;
	
	switch (movement)
	{
	case left:
		playerMove = BK_Vector2(-movementSpeedX, 0);
		break;

	case down:
		playerMove = BK_Vector2(0, -movementSpeedY);
		break;

	case right:
		playerMove = BK_Vector2(movementSpeedX, 0);
		break;
	case up:
		playerMove = BK_Vector2(0, movementSpeedY);
		break;
	case stop:
		playerMove = BK_Vector2(0, 0);
		break;
	default:
		playerMove = BK_Vector2(0, 0);
		break;
	}
	
	objectKinematic.velocity.xVal = playerMove.xVal;
	objectKinematic.velocity.yVal = playerMove.yVal;

	// need to get delta time working
	if (!isStaticObject)
	{
		objectKinematic.position = objectKinematic.position + objectKinematic.velocity * deltaTime;
	
		objectKinematic.rotation = objectKinematic.rotation + objectKinematic.angularVelocity * deltaTime;
	}
	
}
