



#ifndef OBJECT_KINEMATIC_H
#define OBJECT_KINEMATIC_H

#include "BK_Vector.h"

struct a3_Object_Kinematic
{
	BK_Vector2 position;
	float rotation;

	BK_Vector2 velocity;
	float angularVelocity;
};


#endif