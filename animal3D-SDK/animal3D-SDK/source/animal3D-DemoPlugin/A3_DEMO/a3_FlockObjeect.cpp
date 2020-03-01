
#include "A3_DEMO/a3_FlockObject.h"

FlockObject::FlockObject()
{
	object = new a3_TextRenderer();

	objectSeparateBehavior = new Separation_Behavior();
	objectArriveBehavior = new ArriveBehavior();

	objectAlignBehavior = new AlignBehavior();
	FaceBehavior* objectFaceBehavior;
	WanderBehavior* objectWanderBehavior;
}

FlockObject::~FlockObject();

void FlockObject::RenderObject()
{
	//			textRen  PosX						PosY						PosZ   Red	Green Blue  alpha  messageText
	a3textDraw(object, objectKinematic.position.x, objectKinematic.position.y, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, messageText);
}
