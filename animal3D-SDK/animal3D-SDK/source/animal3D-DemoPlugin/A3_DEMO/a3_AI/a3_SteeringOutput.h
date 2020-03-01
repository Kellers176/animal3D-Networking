
#include "animal3D-A3DM/a3math/a3vector.h"

#ifndef STEERING_OUTPUT_H
#define STEERING_OUTPUT_H

struct SteeringOutput
{
	a3vec2 linear;
	float angular;
};

a3vec2 operator * (a3vec2 vector, float multiplier) {
	a3vec2 temp = vector;
	temp.x *= multiplier;
	temp.y *= multiplier;
	return temp;
}

a3vec2 operator += (a3vec2 vector, a3vec2 other) {
	a3vec2 temp = vector;
	temp.x = temp.x + other.x;
	temp.y = temp.y + other.y;
	return temp;
}

a3vec2 operator / (a3vec2 vector, float divider) {
	a3vec2 temp = vector;
	temp.x = temp.x / divider;
	temp.y = temp.y / divider;
	return temp;
}

a3vec2 operator *= (a3vec2 vector, float multiplier) {
	a3vec2 temp = vector;
	temp.x = temp.x * multiplier;
	temp.y = temp.y * multiplier;
	return temp;
}

a3vec2 operator - (a3vec2 vector, a3vec2 other) {
	a3vec2 temp = vector;
	temp.x = vector.x - other.x;
	temp.y = vector.y - other.y;
	return temp;
}

a3vec2 operator -= (a3vec2 vector, a3vec2 other) {
	a3vec2 temp = vector;
	temp.x = temp.x - other.x;
	temp.y = temp.y - other.y;
	return temp;
}

a3vec2 operator + (a3vec2 vector, a3vec2 other) {
	a3vec2 temp = vector;
	temp.x = temp.x + other.x;
	temp.y = temp.y + other.y;
	return temp;
}

SteeringOutput operator + (SteeringOutput thisOne, SteeringOutput other) {
	SteeringOutput temp = thisOne;
	temp.linear = thisOne.linear + other.linear;
	temp.angular = thisOne.angular + other.angular;
	return temp;
}


#endif