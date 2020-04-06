#ifndef ALIGN_H
#define ALIGN_H

class AlignBehavior
{
public:
	AlignBehavior()
	{
		character = Kinematic();
		maxAngularAcc = 2;
		maxRotation = 2;
		targetRadius = 5;
		slowRadius = 10;

		target = Kinematic();
	}

	AlignBehavior(Kinematic newChar, float newMaxAcc, float newMaxRot, float newTargetRad, float newSlowRad)
	{
		character = newChar;
		maxAngularAcc = newMaxAcc;
		maxRotation = newMaxRot;
		targetRadius = newTargetRad;
		slowRadius = newSlowRad;

		target = Kinematic();
	}

	~AlignBehavior()
	{

	}

	float AbsoluteValue(float value)
	{
		float temp;

		if (value < 0)
		{
			temp = value * -1;
		}
		else
		{
			temp = value;
		}

		return temp;
	}


	// holds kinematic  data for teh character and target
	Kinematic character;
	Kinematic target;

	// holds the max angular acceleration and rotation of the character
	float maxAngularAcc;
	float maxRotation;

	// holds the radius for arriving at the target
	float targetRadius;

	// holds the radius for beginning to slow down
	float slowRadius;

	// holds the time over which to achieve target speed
	float timeToTarget = 0.1f;

	// maps the rotation to (-3.14 to 3.14)
	float MapToRange(float newFloat)
	{
		// https://rosettacode.org/wiki/Map_range
		float temp = 0;

		maxRotation;

		float a1, a2, b1, b2, s;

		a1 = -maxRotation;
		a2 = maxRotation;

		b1 = -3.14159f;
		b2 = 3.14159f;

		s = newFloat;

		temp = b1 + ((s - a1) * (b2 - b1)) / (a2 - a1);

		return temp;
	}

	SteeringOutput* getSteering()
	{
		// create the structure to hold the output
		SteeringOutput* steering = new SteeringOutput();

		// get the naive direction to the target
		float rotation = target.orientation - character.orientation;

		// map result to the (-pi, pi) interval
		rotation = MapToRange(rotation);
		float rotationSize = a3absolute(rotation);

		float targetRotation = target.rotation;
		float characterRotation = character.rotation;
		float maxAngularAcceleration = maxAngularAcc;

		// check if we are there, return no steering
		if (rotation < targetRadius)
		{
			return nullptr;
		}

		// if we are outside the sowRadius then use maximum rotation
		if (rotationSize > slowRadius)
		{
			targetRotation = maxRotation;
		}
		else
		{
			targetRotation = maxRotation * rotationSize / slowRadius;
		}

		// the final target rotation combines
		// speed (already in the variable) and direction
		targetRotation += rotation / rotationSize;

		// acceleration treis to get ot the target rotation
		steering->angular = targetRotation - characterRotation;
		steering->angular /= timeToTarget;

		//check if the acceleration is too great
		float angularAcceleration = AbsoluteValue(steering->angular);

		if (angularAcceleration > maxAngularAcceleration)
		{
			steering->angular /= angularAcceleration;
			steering->angular *= maxAngularAcceleration;
		}

		// output the steering 
		a3vec2 zeroVec;
		zeroVec.x = 0;
		zeroVec.y = 0;
		steering->linear = zeroVec;
		return steering;
	}


};

#endif
