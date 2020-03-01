
#include "A3_DEMO/a3_FlockObject.h"

FlockObject::FlockObject()
{
	object = new a3_TextRenderer();

	// objectSeparateBehavior = new Separation_Behavior();
	// objectArriveBehavior = new ArriveBehavior();
	// 
	// objectAlignBehavior = new AlignBehavior();
	// objectFaceBehavior = new FaceBehavior();
	// objectWanderBehavior = new WanderBehavior();

	messageText[0] = 'Y';

	// objectKinematic = Kinematic();

	unitID = 0;

}

FlockObject::~FlockObject()
{
	// delete objectSeparateBehavior;
	// delete objectArriveBehavior;
	// 
	// delete objectAlignBehavior;
	// delete objectFaceBehavior;
	// delete objectWanderBehavior;
	// 
	delete object;
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
