#ifndef FACE_H
#define FACE_H

#include "a3_Align_Behavior.h"
#include "animal3D-A3DM/a3math/a3trig.h"

#include "BK_Vector.h"
#include "a3_ObjectKinematic.h"
#include "SteeringOutput.h"

class FaceBehavior
{
public:
	FaceBehavior()
	{
		faceTarget = a3_Object_Kinematic();
	}

	FaceBehavior(a3_Object_Kinematic newTarget)
	{
		faceTarget = newTarget;
	}

	~FaceBehavior()
	{

	}

	// overrides the align.target member
	a3_Object_Kinematic faceTarget;

	// ... other data is derived from the superclass

	// implemented as it was in pursue
	SteeringOutput* GetSteering(AlignBehavior* align)
	{
		// calculate the target to delegate to align
		// work out the direction to target
		a3vec2 direction;
		direction.x = faceTarget.position.xVal - align->character.position.xVal;
		direction.y = faceTarget.position.yVal - align->character.position.yVal;

		// check for a zero direction and make no change if so
		float directionMagnitude = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (directionMagnitude == 0)
		{
			//return target;
		}

		// put the target togather
		align->target = faceTarget;
		align->target.rotation = a3atan2d(-direction.x, direction.y);

		// delegate to align
		return align->getSteering();
	}

};

#endif 