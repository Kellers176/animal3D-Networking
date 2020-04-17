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

}

a3_Object::~a3_Object()
{
	//unloads the text

}

void a3_Object::a3_RenderObject(a3_TextRenderer* newRenderer)
{
	//-1,-1,-1 is bottom left corner
	//draw text
	a3textDraw(newRenderer, objectKinematic.position.xVal, objectKinematic.position.yVal, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, objectShape[0]);
}


void a3_Object::a3_UpdateKinematics(float deltaTime)
{
	// update teh position;
	if (!isStaticObject)
	{
		objectKinematic.position = objectKinematic.position + objectKinematic.velocity * deltaTime;

		objectKinematic.rotation = objectKinematic.rotation + objectKinematic.angularVelocity * deltaTime;
	}
}
