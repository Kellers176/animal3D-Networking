
#ifndef FLOCK_OBJECT_H
#define FLOCK_OBJECT_H

#include "A3_DEMO/a3_AI/a3_Kinematic.h"
#include "A3_DEMO/a3_AI/a3_Align_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Arrive_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Face_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Separation_Behavior.h"
#include "A3_DEMO/a3_AI/a3_Wander_Behavior.h"

#include "animal3D-A3DG/a3graphics/a3_TextRenderer.h"

class FlockObject
{
public:
	FlockObject();
	~FlockObject();

	void UpdateFlockObject(float deltaTime);

	void RenderObject();

	int GetUnitID() { return unitID; }

	float GetPosX() { return objectKinematic.positionX; }
	float GetPosY() { return objectKinematic.positionY; }

	void SetUnitID(int newID);
	void SetPosition(float newX, float newY);

private:
	int unitID;

	char messageText[1];

	a3_TextRenderer* object;

	// need this for steering operations
	Kinematic objectKinematic;
	Kinematic targetKinematic;
	//

};

#endif