

#ifndef FACE_H
#define FACE_H

#include "a3_Align_Behavior.h"
#include "a3_Kinematic.h"

class FaceBehavior
{
public:
	FaceBehavior()
	{
		faceTarget = Kinematic();
	}

	~FaceBehavior()
	{

	}

	// overrides the align.target member
	Kinematic faceTarget;

	// ... other data is derived from the superclass

	// implemented as it was in pursue
	SteeringOutput* GetSteering(AlignBehavior* align)
	{
		// calculate the target to delegate to align
		// work out the direction to target
		a3vec2 direction = faceTarget.position - align->character.position;

		// check for a zero direction and make no change if so
		float directionMagnitude = a3sqrt(direction.x * direction.x + direction.y * direction.y);

		if (directionMagnitude == 0)
		{
			//return target;
		}

		// put the target togather
		align->target = faceTarget;
		align->target.orientation = a3atan2d(-direction.x, direction.y);

		// delegate to align
		return align->getSteering();
	}

};

#endif