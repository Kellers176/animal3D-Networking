


#ifndef SEPARATION_H
#define SEPARATION_H

class Separation_Behavior
{
public:
	Separation_Behavior()
	{
		character = Kinematic();

		for (int i = 0; i < 10; i++)
		{
			targetsArray[i] = Kinematic();
		}

		float threshold = 5;

		float coefficient = 0.3f;

		float maxAcceleration = 2;
	}

	Separation_Behavior(Kinematic newCharKin, Kinematic newListOfOtherKin[10], float newThreshold, float newDecayCoeff, float newMaxAcc)
	{
		character = newCharKin;

		for (int i = 0; i < 10; i++)
		{
			targetsArray[i] = newListOfOtherKin[i];
		}

		threshold = newThreshold;

		decayCoefficient = newDecayCoeff;

		maxAcceleration = newMaxAcc;
	}

	~Separation_Behavior()
	{

	}

	// holds the kinematic data for the character
	Kinematic character;

	// holds a list of potential targets
	Kinematic targetsArray[10];

	// holds the threshold to take action
	float threshold;

	// holds the constant coefficient of decay for the inverse square law force
	float decayCoefficient;

	// holds the maximum acceleration of the character 
	float maxAcceleration;

	// see the implementation nots for why we have two get steering methods
	SteeringOutput* getSteering()
	{
		// the steering variable holds the output
		SteeringOutput* steering = new SteeringOutput();

		// loop througheach target
		// foreach loop
		for(Kinematic target : targetsArray)
		{
			// check if the target is close
			a3vec2 direction;
			direction.x = target.positionX - character.positionX;
			direction.y = target.positionY - character.positionY;
			float distance = a3sqrt(direction.x * direction.x + direction.y * direction.y);

			if(distance < threshold)
			{
				// calculate the strength of repulsion
				float strength = a3minimum(decayCoefficient / (distance * distance), maxAcceleration);

				// add the acceleration
				// normalize teh direction
				direction.x = direction.x / distance;
				direction.y = direction.y / distance;
				steering->linear.x +=  direction.x * strength;
				steering->linear.y +=  direction.y * strength;
			}
		}

		// we've gone through all the targets, return the result
		return steering;
	}
	
};

#endif