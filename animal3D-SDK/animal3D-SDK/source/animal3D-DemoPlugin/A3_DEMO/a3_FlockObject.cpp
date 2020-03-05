
#include "A3_DEMO/a3_FlockObject.h"

FlockObject::FlockObject()
{
	object = new a3_TextRenderer();

	messageText[0] = 'Y';

	objectKinematic = Kinematic();
	targetKinematic = objectKinematic;

	unitID = 0;

}

FlockObject::~FlockObject()
{
	// 
	delete object;
}

void FlockObject::UpdateFlockObject(float deltaTime)
{
	objectKinematic.Update(5, deltaTime);
}


void FlockObject::RenderObject()
{
	//			textRen  PosX						PosY						PosZ   Red	Green Blue  alpha  messageText
	a3textDraw(object, objectKinematic.positionX, objectKinematic.positionY, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, messageText);
}

void FlockObject::SetPosition(float newX, float newY)
{
	objectKinematic.positionX = newX;
	objectKinematic.positionY = newY; 
}

void FlockObject::SetUnitID(int newID)
{
	unitID = newID; 
}
