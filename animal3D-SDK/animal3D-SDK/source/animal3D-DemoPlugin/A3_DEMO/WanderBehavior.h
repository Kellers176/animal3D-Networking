#ifndef WANDER_H
#define WANDER_H

#include "animal3D-A3DM/a3math/a3random.h"

#include "BK_Vector.h"
#include "a3_ObjectKinematic.h"
#include "SteeringOutput.h"
#include "a3_Align_Behavior.h"
#include "a3_Face_Behavior.h"

#include <math.h>

class WanderBehavior
{
public:
	WanderBehavior()
	{
		wanderOffset = 3;
		wanderRadius = 3;
		wanderRate = 0.5f;
		maxAcceleration = 2;
		character = a3_Object_Kinematic();

		target = a3_Object_Kinematic();

		wanderOrientation = 0;
	}

	WanderBehavior(float newOffset, float newRadius, float newRate, float newMaxAcc, a3_Object_Kinematic newCharKin)
	{
		wanderOffset = newOffset;
		wanderRadius = newRadius;
		wanderRate = newRate;
		maxAcceleration = newMaxAcc;
		character = newCharKin;

		target = a3_Object_Kinematic();

		wanderOrientation = 0;

	}

	~WanderBehavior()
	{

	}

	BK_Vector2 DirectionToVector(float direction)
	{
		BK_Vector2 temp;

		temp.xVal = (float)cos(direction * 180 / 3.141597f);
		temp.yVal = (float)sin(direction * 180 / 3.141597f);

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
	a3_Object_Kinematic target;
	a3_Object_Kinematic character;

	SteeringOutput* getSteering(AlignBehavior* align, FaceBehavior* face)
	{
		// Calculate the target delegate to face

		// update wander orientation
		wanderOrientation += a3randomNormalized() * wanderRate;

		// caalculate the combined target orientation
		float targetOrientation = wanderOrientation + character.rotation;

		// calculate the center of the wander cycle

		BK_Vector2 targetLocation;
		targetLocation.xVal = character.position.xVal + DirectionToVector(character.rotation).xVal * wanderOffset;
		targetLocation.yVal = character.position.yVal + DirectionToVector(character.rotation).yVal * wanderOffset;

		// calculate the target location
		targetLocation.xVal += DirectionToVector(targetOrientation).xVal * wanderRadius;
		targetLocation.yVal += DirectionToVector(targetOrientation).yVal * wanderRadius;

		// AlignBehavior* alignSteering = new AlignBehavior();
		target.position.xVal = targetLocation.xVal;
		target.position.yVal = targetLocation.yVal;
		face->faceTarget = target;

		// delegate to face
		SteeringOutput* steering = face->GetSteering(align);

		// now set the linear acceleration to be at full acceleration to be at full 
		// acceleration in the direction of the orientation
		steering->linear.xVal = DirectionToVector(character.rotation).xVal * maxAcceleration;
		steering->linear.yVal = DirectionToVector(character.rotation).yVal * maxAcceleration;

		// return it
		return steering;
	}

};

#endif