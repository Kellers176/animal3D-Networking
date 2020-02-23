
#include "a3_SteeringOutput.h"
#include "a3_Kinematic.h"
#include <iostream>

#ifndef SEPARATION_H
#define SEPARATION_H

class Separation_Behavior
{
public:
	Separation_Behavior();
	~Separation_Behavior();

	// holds the kinematic data for the character
	Kinematic character;

	// holds a list of potential targets
	Kinematic targetsArray[10];

	// holds the threshold to take action
	float threshold;

	// holds the constant coefficient of decay for the inverse square law force
	float decayCoefficient;

	// holds the maximum acceleration of the character 
	float maxAcceleration;

	// see the implementation nots for why we have two get steering methods
	SteeringOutput* getSteering()
	{
		// the steering variable holds the output
		SteeringOutput* steering = new SteeringOutput();

		// loop througheach target
		// foreach loop
		for(Kinematic target : targetsArray)
		{
			// check if the target is close
			a3vec2 direction = target.position - character.position;
			float distance = a3sqrt(direction.x * direction.x + direction.y * direction.y);

			if(distance < threshold)
			{
				// calculate the strength of repulsion
				float strength = a3minimum(decayCoefficient / (distance * distance), maxAcceleration);

				// add the acceleration
				// normalize teh direction
				direction = direction / distance;
				steering->linear +=  direction * strength;
			}
		}

		// we've gone through all the targets, return the result
		return steering;
	}
	
};

#endif