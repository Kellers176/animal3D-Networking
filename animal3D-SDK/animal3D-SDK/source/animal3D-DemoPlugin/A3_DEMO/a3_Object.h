

#ifndef A3_OBJECT_H
#define A3_OBJECT_H

#include "animal3D-A3DG/a3graphics/a3_TextRenderer.h"
#include "a3_ObjectKinematic.h"

#include "SteeringOutput.h"
#include "a3_Align_Behavior.h"
#include "a3_Face_Behavior.h"
#include "a3_Arrive_Behavior.h"
#include "a3_Seperation_Behavior.h"
#include "WanderBehavior.h"

class a3_Object
{
public:
	a3_Object();
	~a3_Object();

	void a3_RenderObject(a3_TextRenderer* newRenderer);

	void a3_UpdateSteering(float deltaTime);

	void a3_UpdateKinematics(float deltaTime);

	void setObjectUserID(int newUserID) { userID = newUserID; }

	void setObjectPos(float newX, float newY) { objectKinematic.position = BK_Vector2(newX, newY); }
	void setObjectVelocity(float newVelX, float newVelY) { objectKinematic.velocity = BK_Vector2(newVelX, newVelY); }
	void setObjectRotation(float newRotation) { objectKinematic.rotation = newRotation; }
	void setObjectID(int newID) { objectID = newID; }

	int getObjectID() { return objectID; }
	int getUserID() { return userID; }
	BK_Vector2 getPosition() { return objectKinematic.position; }
	BK_Vector2 getVelocity() { return objectKinematic.velocity; }

private:
	const a3byte* objectShape[1];

	a3_Object_Kinematic objectKinematic;

	int userID;
	int objectID;
};


#endif // A3_OBJECT_H
