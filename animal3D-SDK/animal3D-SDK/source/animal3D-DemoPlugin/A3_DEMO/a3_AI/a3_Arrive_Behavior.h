
#include "a3_Kinematic.h"

#ifndef ARRIVE_H
#define ARRIVE_H

class ArriveBehavior
{
public:
	ArriveBehavior();
	~ArriveBehavior();

	// holds the kinematic data for the character and target
	Kinematic character;
	Kinematic target;

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
		a3vec2 direction = target.position - character.position;
		float distance = a3sqrt(direction.x * direction.x + direction.y * direction.y);

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
		float velMag = a3sqrt(targetVelocity.x * targetVelocity.x + targetVelocity.y * targetVelocity.y);
		targetVelocity = targetVelocity / velMag;

		// make the velocity the target speed
		targetVelocity *= targetSpeed;

		// acceleration tries to get to the target velocity
		steering->linear = targetVelocity - character.velocity;
		steering->linear = steering->linear / timeToTarget;

		// check if the acceleration is too fast
		float linearMag = a3sqrt(steering->linear.x * steering->linear.x + steering->linear.y * steering->linear.y);
		if (linearMag > maxAcceleration)
		{ 
			// normalize the linear
			steering->linear = steering->linear / linearMag;
			steering->linear *= maxAcceleration;
		}

		// output the steering 
		steering->angular = 0;
		return steering;
	}



};

#endif
