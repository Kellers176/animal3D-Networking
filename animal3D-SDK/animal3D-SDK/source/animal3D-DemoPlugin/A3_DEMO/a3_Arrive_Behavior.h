#ifndef ARRIVE_H
#define ARRIVE_H

#include "BK_Vector.h"
#include "a3_ObjectKinematic.h"
#include "SteeringOutput.h"

class ArriveBehavior
{
public:
	ArriveBehavior()
	{
		character = a3_Object_Kinematic();
		target = a3_Object_Kinematic();

		maxAcceleration = 1;
		maxSpeed = 3;

		slowRadius = 5;

		targetRadius = 2;
	}

	ArriveBehavior(a3_Object_Kinematic newCharKin, float newMaxAcc, float newMaxSpeed, float newSlowRadius, float newTargetRadius)
	{
		character = newCharKin;
		target = a3_Object_Kinematic();

		maxAcceleration = newMaxAcc;
		maxSpeed = newMaxSpeed;

		slowRadius = newSlowRadius;

		targetRadius = newTargetRadius;
	}

	~ArriveBehavior()
	{

	}

	// holds the kinematic data for the character and target
	a3_Object_Kinematic character;
	a3_Object_Kinematic target;

	// holds the max acceleration and speed of the character
	float maxAcceleration;
	float maxSpeed;

	// holds the radius for arriving at the target
	float targetRadius;

	// holds the radius for beginning to slow down
	float slowRadius;

	// holds teh time over which to achieve target speed
	float timeToTarget = 0.1f;

	SteeringOutput* getSteering()
	{
		// create teh structure to hold our output
		SteeringOutput* steering = new SteeringOutput();

		float targetSpeed = 0;

		// get the direction to the target
		a3vec2 direction;
		direction.x = target.position.xVal - character.position.xVal;
		direction.y = target.position.yVal - character.position.yVal;
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		// check if we are there, return no steering
		if (distance < targetRadius)
		{
			return nullptr;
		}

		// if we are outside the slowRadius, the we go to max speed
		if (distance > slowRadius)
		{
			targetSpeed = maxSpeed;
		}
		else
		{
			targetSpeed = maxSpeed * distance / slowRadius;
		}

		// the target velocity combines speed and direction
		a3vec2 targetVelocity = direction;

		// normalize the velocity
		float velMag = sqrtf(targetVelocity.x * targetVelocity.x + targetVelocity.y * targetVelocity.y);
		targetVelocity.x = targetVelocity.x / velMag;
		targetVelocity.y = targetVelocity.y / velMag;

		// make the velocity the target speed
		targetVelocity.x *= targetSpeed;
		targetVelocity.y *= targetSpeed;

		// acceleration tries to get to the target velocity
		steering->linear.xVal = targetVelocity.x - character.velocity.xVal;
		steering->linear.yVal = targetVelocity.y - character.velocity.yVal;
						  
		steering->linear.xVal = steering->linear.xVal / timeToTarget;
		steering->linear.yVal = steering->linear.yVal / timeToTarget;

		// check if the acceleration is too fast
		float linearMag = sqrtf(steering->linear.xVal * steering->linear.xVal + steering->linear.yVal * steering->linear.yVal);
		if (linearMag > maxAcceleration)
		{
			// normalize the linear
			steering->linear.xVal = steering->linear.xVal / linearMag;
			steering->linear.yVal = steering->linear.yVal / linearMag;
			steering->linear.xVal *= maxAcceleration;
			steering->linear.yVal *= maxAcceleration;
		}

		// output the steering 
		steering->angular = 0;
		return steering;
	}



};

#endif
