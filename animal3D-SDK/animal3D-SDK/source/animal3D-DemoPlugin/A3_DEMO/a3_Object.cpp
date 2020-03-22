#include "a3_Object.h"
#include <GL/glew.h>

#include <iostream>
#include <string>
a3_Object::a3_Object()
{
	//set default position
	objectKinematic.position.xVal = -0.99f;
	objectKinematic.position.yVal = -0.95f;
	
	//create shape
	objectShape[0] = "T";

	//creates and initalizes the objectRenderer
	a3textInitialize(objectRenderer, 18, 1, 0, 0, 0);

	objectID = 0;

}

a3_Object::~a3_Object()
{
	//unloads the text
	a3textRelease(objectRenderer);
}

void a3_Object::a3_RenderObject()
{
	//clear the screen then draw
	glClear(GL_COLOR_BUFFER_BIT);
	//-1,-1,-1 is bottom left corner
	//draw text
	a3textDraw(objectRenderer, objectKinematic.position.xVal, objectKinematic.position.yVal, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, objectShape[0]);
}


void a3_Object::a3_UpdateKinematics(float deltaTime)
{
	// update teh position;
	objectKinematic.position = objectKinematic.position + objectKinematic.velocity;

	objectKinematic.rotation = objectKinematic.rotation + objectKinematic.angularVelocity;
}
