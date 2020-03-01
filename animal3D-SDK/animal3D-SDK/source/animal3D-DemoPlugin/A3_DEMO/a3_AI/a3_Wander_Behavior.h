

#ifndef WANDER_H
#define WANDER_H

#include "a3_Face_Behavior.h"
#include "animal3D-A3DM/a3math/a3random.h"

a3vec2 DirectionToVector(float direction)
{
	a3vec2 temp;

	temp.x = a3cosd(direction);
	temp.y = a3sind(direction);

	return temp;
}

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

		a3vec2 targetLocation = character.position + DirectionToVector(character.orientation) * wanderOffset;

		// calculate the target location
		targetLocation += DirectionToVector(targetOrientation) * wanderRadius;

		// AlignBehavior* alignSteering = new AlignBehavior();
		target.position = targetLocation;
		face->faceTarget = target;

		// delegate to face
		SteeringOutput* steering = face->GetSteering(align);

		// now set the linear acceleration to be at full acceleration to be at full 
		// acceleration in the direction of the orientation
		steering->linear = DirectionToVector(character.orientation) * maxAcceleration;

		// return it
		return steering;
	}

};

#endif