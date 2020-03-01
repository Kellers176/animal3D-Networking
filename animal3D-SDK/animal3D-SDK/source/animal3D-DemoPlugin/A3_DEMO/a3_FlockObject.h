
#include "A3_DEMO/a3_AI/a3_Align_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Arrive_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Face_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Separation_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Wander_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Kinematic.h"
#include "A3_DEMO/a3_AI/a3_SteeringOutput.h"

#include "animal3D-A3DG/a3graphics/a3_TextRenderer.h"


#ifndef FLOCK_OBJECT_H
#define FLOCK_OBJECT_H

class FlockObject
{
public:
	FlockObject();
	~FlockObject();

	void RenderObject();

	void SetUnitID(int newID) { unitID = newID; }
	void SetPosition(int newX, int newY) { objectKinematic.position.x = newX; objectKinematic.position.y = newY; }

private:
	int unitID;

	char messageText[1] = 'Y';

	a3_TextRenderer* object;

	// need this for steering operations
	Kinematic objectKinematic;

	// steering operations
	Separation_Behavior* objectSeparateBehavior;
	ArriveBehavior* objectArriveBehavior;

	AlignBehavior* objectAlignBehavior;
	FaceBehavior* objectFaceBehavior;
	WanderBehavior* objectWanderBehavior;
};

#endif