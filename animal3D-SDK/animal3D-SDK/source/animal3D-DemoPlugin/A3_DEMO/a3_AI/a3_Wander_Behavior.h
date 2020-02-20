

#ifndef WANDER_H
#define WANDER_H

#include "a3_Face_Behavior.h"

class WanderBehavior : FaceBehavior
{
public:
	// holds the radius and forward offset of the wander circle
	// wanderOffset
	// wanderRadius

	// holds the maximum rate at which the wander orientation can change
	// wanderRate

	// holds the current orientation of the wander target
	// wanderOrientation

	// holds teh maximum acceleration of the character
	// maxAcceleration

	// again we dont need a new target

	// ... other data is derived from super class

	/*
	// def getSteering()
	// {
	//		// Calculate the target delegate to face
	//		
	//		// update wander orientation
	//		wanderOrientation = += randomBinomial() * wanderRate;
	//
	//		// caalculate the combined target orientation
	//		targetOrientation = wanderOrientation + character.orientation;

	//		// calculate the center of the wander cycle
	//		target = character.position + wanderOffset * character.orientation.AsVector();
	//
	//		// calculate the target location
	//		target += wanderRadius * targetOrientation.AsVector();
	//
	//		// delegate to face
	//		steering = Face.getSteering();
	//
	//		// now set the linear acceleration to be at full acceleration to be at full 
	//		// acceleration in the direction of the orientation
	//		steering.linear - maxAcceleration * character.orientation.AsVector();
	//
	//		// return it
	//		return steering;
	// }

	*/
private:
};

#endif