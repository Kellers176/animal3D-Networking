
#include "animal3D-A3DM/a3math/a3vector.h"

#ifndef STEERING_OUTPUT_H
#define STEERING_OUTPUT_H

struct SteeringOutput
{
	a3vec2 linear;
	float angular;
};

SteeringOutput operator + (SteeringOutput thisOne, SteeringOutput other) {
	Steeringoutput temp = thisOne;
	temp.linear = thisOne.linear + other.linear;
	temp.angular = thisOne.linear + other.linear;
	return temp;
}

SteeringOutput* operator + (SteeringOutput* thisOne, SteeringOutput* other) {
	Steeringoutput* temp = new SteeringOutput();
	temp->linear = thisOne->linear + other->linear;
	temp->angular = thisOne->linear + other->linear;
	return temp;
}


#endif