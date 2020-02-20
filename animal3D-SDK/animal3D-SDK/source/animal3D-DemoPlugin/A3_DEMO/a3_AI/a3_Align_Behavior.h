

#ifndef ALIGN_H
#define ALIGN_H

class AlignBehavior 
{
public:
	// holds kinematic  data for teh character and target
	// character
	// target

	// holds the mas angular acceleration and rotation of the character
	// maxAngularAccleration
	// maxRotation

	// holds the radius for arriving at the target
	// target radius

	// holds the radius for beginning to slowd down
	// slowRadius

	// holds the time over which to achieve target speed
	// timeToTarget = 0.1

	/*
	// def getSteering(target)
	// {
	//		// create the structure to hold the output
	//		steering = new SteeringOutput();
	//		
	//		// get the naive direction to the target
	//		rotation = target.orientation - character.orientation
	//		
	//		// map result to the (-pi, pi) interval
	//		rotation = mapToRange(rotation);
	//		rotationSize = abs(rotation);
	//
	//		// check if we are there, return no steering
	//		if rotation < target Radius
	//		{
	//			return 0;
	//		}
	//
	//		// if we are outside the sowRadius then use maximum rotation
	//		if rotationSize > slowRadius
	//		{
	//			targetRotation = maxRotation;
	//		}
	//		else
	//		{
	//			targetRotation = maxRotation * rotationSize / slowRadius
	//		}
	//		
	//		// the final target rotation combines
	//		// speed (already in the variable) and direction
	//		targetRotation += rotation / rotationSize
	//
	//		// acceleration treis to get ot the target rotation
	//		steering.angular = targetRotation - characterRotation;
	//		steering.angular /= timeToTarget
	//
	//		check if the acceleration is too great
	//		angularAcceleration = abs(steering.angular)
	//		if angularAcceleration > maxAngularAcceleration
	//		{
	//			steering.angular /= angularAcceleration
	//			steering.angular *= maxAngularAcceleration
	//		}
	//
	//		// output the steering 
	//		steering.linear = 0;
	//		return steering;
	// }
	*/
private:

};

#endif
