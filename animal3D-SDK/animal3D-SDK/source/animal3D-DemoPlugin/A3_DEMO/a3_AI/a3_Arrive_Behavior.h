

#ifndef ARRIVE_H
#define ARRIVE_H

class ArriveBehavior
{
public:
	ArriveBehavior()
	{
		character = Kinematic();
		target = Kinematic();

		maxAcceleration = 1;
		maxSpeed = 3;

		slowRadius = 5;

		targetRadius = 2;
	}

	ArriveBehavior(Kinematic newCharKin, float newMaxAcc, float newMaxSpeed, float newSlowRadius, float newTargetRadius)
	{
		character = newCharKin;
		target = Kinematic();

		maxAcceleration = newMaxAcc;
		maxSpeed = newMaxSpeed;

		slowRadius = newSlowRadius;

		targetRadius = newTargetRadius;
	}

	~ArriveBehavior()
	{

	}

	// holds the kinematic data for the character and target
	Kinematic character;
	Kinematic target;

	// holds the max acceleration and speed of the character
	float maxAcceleration;
	float maxSpeed;
	
	// holds the radius for arriving at the target
	float targetRadius;

	// holds the radius for beginning to slow down
	float slowRadius;

	// holds teh time over which to achieve target speed
	float timeToTarget = 0.1f;

	SteeringOutput* getSteering()
	{
		// create teh structure to hold our output
		SteeringOutput* steering = new SteeringOutput();

		float targetSpeed = 0;

		// get the direction to the target
		a3vec2 direction;
		direction.x = target.positionX - character.positionX;
		direction.y = target.positionY - character.positionY;
		float distance = a3sqrt(direction.x * direction.x + direction.y * direction.y);

		// check if we are there, return no steering
		if (distance < targetRadius)
		{
			return nullptr;
		}

		// if we are outside the slowRadius, the we go to max speed
		if (distance > slowRadius)
		{
			targetSpeed = maxSpeed;
		}
		else 
		{
			targetSpeed = maxSpeed * distance / slowRadius;
		}

		// the target velocity combines speed and direction
		a3vec2 targetVelocity = direction;

		// normalize the velocity
		float velMag = a3sqrt(targetVelocity.x * targetVelocity.x + targetVelocity.y * targetVelocity.y);
		targetVelocity.x = targetVelocity.x / velMag;
		targetVelocity.y = targetVelocity.y / velMag;

		// make the velocity the target speed
		targetVelocity.x *= targetSpeed;
		targetVelocity.y *= targetSpeed;

		// acceleration tries to get to the target velocity
		steering->linear.x = targetVelocity.x - character.velocityX;
		steering->linear.y = targetVelocity.y - character.velocityY;

		steering->linear.x = steering->linear.x / timeToTarget;
		steering->linear.y = steering->linear.y / timeToTarget;

		// check if the acceleration is too fast
		float linearMag = a3sqrt(steering->linear.x * steering->linear.x + steering->linear.y * steering->linear.y);
		if (linearMag > maxAcceleration)
		{ 
			// normalize the linear
			steering->linear.x = steering->linear.x / linearMag;
			steering->linear.y = steering->linear.y / linearMag;
			steering->linear.x *= maxAcceleration;
			steering->linear.y *= maxAcceleration;
		}

		// output the steering 
		steering->angular = 0;
		return steering;
	}



};

#endif
