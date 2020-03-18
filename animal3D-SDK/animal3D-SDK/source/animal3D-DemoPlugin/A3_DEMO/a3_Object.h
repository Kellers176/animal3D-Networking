

#ifndef A3_OBJECT_H
#define A3_OBJECT_H

#include "animal3D-A3DG/a3graphics/a3_TextRenderer.h"
#include "a3_ObjectKinematic.h"

class a3_Object
{
public:
	a3_Object();
	~a3_Object();

	void a3_RenderObject();

	void a3_UpdateKinematics();

	void setObjectPos(float newX, float newY) { objectKinematic.position = BK_Vector2(newX, newY); }

private:
	a3_TextRenderer objectRenderer[1];
	const a3byte* objectShape[1];

	a3_Object_Kinematic objectKinematic;
};


#endif // A3_OBJECT_H
