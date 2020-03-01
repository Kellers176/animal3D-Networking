

#ifndef WANDER_H
#define WANDER_H

#include "animal3D-A3DM/a3math/a3random.h"

class WanderBehavior : public FaceBehavior
{
public:
	WanderBehavior()
	{
		wanderOffset = 3;
		wanderRadius = 3;
		wanderRate = 0.5f;
		maxAcceleration = 2;
		character = Kinematic();

		target = Kinematic();

		wanderOrientation = 0;
	}

	WanderBehavior(float newOffset, float newRadius, float newRate, float newMaxAcc, Kinematic newCharKin)
	{
		wanderOffset = newOffset;
		wanderRadius = newRadius;
		wanderRate = newRate;
		maxAcceleration = newMaxAcc;
		character = newCharKin;

		target = Kinematic();

		wanderOrientation = 0;

	}

	~WanderBehavior()
	{

	}

	a3vec2 DirectionToVector(float direction)
	{
		a3vec2 temp;

		temp.x = a3cosd(direction);
		temp.y = a3sind(direction);

		return temp;
	}

	// holds the radius and forward offset of the wander circle
	float wanderOffset;
	float wanderRadius;

	// holds the maximum rate at which the wander orientation can change
	float wanderRate;

	// holds the current orientation of the wander target
	float wanderOrientation;

	// holds teh maximum acceleration of the character
	float maxAcceleration;

	// again we dont need a new target

	// ... other data is derived from super class
	Kinematic target;
	Kinematic character;

	SteeringOutput* getSteering(AlignBehavior* align, FaceBehavior* face)
	{
		// Calculate the target delegate to face
		
		// update wander orientation
		wanderOrientation += a3randomNormalized()* wanderRate;

		// caalculate the combined target orientation
		float targetOrientation = wanderOrientation + character.orientation;

		// calculate the center of the wander cycle

		a3vec2 targetLocation;
		targetLocation.x = character.positionX + DirectionToVector(character.orientation).x * wanderOffset;
		targetLocation.y = character.positionY + DirectionToVector(character.orientation).y * wanderOffset;

		// calculate the target location
		targetLocation.x += DirectionToVector(targetOrientation).x * wanderRadius;
		targetLocation.y += DirectionToVector(targetOrientation).y * wanderRadius;

		// AlignBehavior* alignSteering = new AlignBehavior();
		target.positionX = targetLocation.x;
		target.positionY = targetLocation.y;
		face->faceTarget = target;

		// delegate to face
		SteeringOutput* steering = face->GetSteering(align);

		// now set the linear acceleration to be at full acceleration to be at full 
		// acceleration in the direction of the orientation
		steering->linear.x = DirectionToVector(character.orientation).x * maxAcceleration;
		steering->linear.y = DirectionToVector(character.orientation).y * maxAcceleration;

		// return it
		return steering;
	}

};

#endif