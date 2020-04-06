#include "animal3D-A3DM/a3math/a3vector.h"
#include "A3_DEMO/BK_Vector.h"

#ifndef STEERING_OUTPUT_H
#define STEERING_OUTPUT_H

struct SteeringOutput
{
	BK_Vector2 linear;
	float angular;
};

#endif