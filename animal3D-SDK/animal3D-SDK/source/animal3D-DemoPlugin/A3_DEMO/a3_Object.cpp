#include "a3_Object.h"
#include <GL/glew.h>

#include <iostream>
#include <string>
a3_Object::a3_Object()
{
	//set default position
	objectKinematic = a3_Object_Kinematic();

	objectKinematic.position.xVal = 0.0f;
	objectKinematic.position.yVal = 0.0f;
	
	//create shape
	objectShape[0] = "O";

	userID = 0;
	objectID = 0;

}

a3_Object::~a3_Object()
{
	//unloads the text

}

void a3_Object::a3_RenderObject(a3_TextRenderer* newRenderer)
{
	//-1,-1,-1 is bottom left corner
	//draw text
	a3textDraw(newRenderer, objectKinematic.position.xVal, objectKinematic.position.yVal, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, *objectShape);
}


void a3_Object::a3_UpdateKinematics(float deltaTime)
{
	// update teh position;
	objectKinematic.position = objectKinematic.position + objectKinematic.velocity * deltaTime;

	objectKinematic.rotation = objectKinematic.rotation + objectKinematic.angularVelocity * deltaTime;
}

void a3_Object::a3_UpdateSteering(float deltaTime)
{
	// calculate steering

	// steering = separation + wander

	// velocity = steering.linear 

	objectKinematic.position = objectKinematic.position + objectKinematic.velocity * deltaTime;
}
