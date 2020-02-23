
#include "a3_SteeringOutput.h"
#include "animal3D-A3DM/a3math/a3sqrt.h"

#ifndef KINEMATIC_H
#define KINEMATIC_H

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
	temp.y = temp.y /divider;
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
	temp.x = temp.x - other.x;
	temp.y = temp.y - other.y;
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

struct Kinematic
{
	a3vec2 position;
	float orientation;
	a3vec2 velocity;
	float rotation;

	void Update(SteeringOutput steering, float maxSpeed, float deltaTime)
	{
		// update the position and orientation
		position += velocity * deltaTime;
		orientation += steering.angular * deltaTime;
		
		// check for speeding and clip
		float velocityMagnitude = a3sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		
		if (velocityMagnitude > maxSpeed)
		{
			velocity = velocity / velocityMagnitude;
			velocity *= maxSpeed;
		}
	}

};

#endif