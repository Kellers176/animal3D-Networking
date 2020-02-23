
#include "a3_SteeringOutput.h"
#include "a3_Kinematic.h"
#ifndef SEEK_H
#define SEEK_H

class SeekBehavior
{
public:
	// holds the kinematic data for the character and target
	Kinematic target;
	Kinematic character;

	// holds the maximum acceleration of the character
	float maxAcceleration;

	// returns the desired steering output
	SteeringOutput* getSteering()
	{
		// create the structure to hold our output
		SteeringOutput* steering = new SteeringOutput();
		
		// get the direction to the target
		steering->linear = target.position - character.position;
		
		// normalise the linear vector
		float linearMagnitude = a3sqrt(steering->linear.x * steering->linear.x + steering->linear.y * steering->linear.y);
		steering->linear / linearMagnitude;

		// give full accleration along this direction
		steering->linear *= maxAcceleration;
		
		// output the steering 
		steering->angular = 0; 
		return steering;
	}



private:

};


#endif