

#ifndef FACE_H
#define FACE_H

#include "a3_Align_Behavior.h"

class FaceBehavior : AlignBehavior
{
public:
	// overrides the align.target member
	// target

	// ... other data is derived from the superclass

	// implemented as it was in pursue
	// def getSteering()
	// {
	//		// calculate the target to delegat to align
	//		
	//		// work ou the direction to target
	//		direction = target.position - character.position
	//	
	//		// check for a zero direction, and make no change if so
	//		if direction.length() == 0;
	//		{
	//			return target;
	//		}
	//
	//		// put the target together
	//		align.targte = explicitTarget;
	//		align.target.orientation = atan2(-direction.x, direction.z)
	//
	//		// delegate to align
	//		return Align.getSteering();
	// }

private:

};

#endif