

#ifndef ARRIVE_H
#define ARRIVE_H

class ArriveBehavior
{
public:
	// holds the kinematic data for the character and target
	// character
	// target

	// holds the max acceleration and speed of the character
	// maxAcceleration
	// maxSpeed
	
	// holds the radius for arriving at the target
	// targetRadius

	// holds the radius for beginning to slow down
	// slowRadius

	// holds teh time over which to achieve target speed
	// timeToTarget = 0.1

	/*
		def getSteering(target)
		{
			// create teh structure to hold our output
			// steering = new SteeringOutput();

			// get the direction to the target
			// direction = target.position - character.position
			// distance = direction.length();

			// check if we are there, return no steering
			// if distance < targetRadius
			// {
			//		return;
			// }

			// if we are outside the slowRadius, the we go to max speed
			// if distance > slowRadius
			// {
			//		targetSpeed = maxSpeed
			// }
			// else 
			// {
			//		targetSpeed = maxSpeed * distance / slowRadius
			// }

			// the target velocity combines speed and direction
			// targetVelocity = direction 
			// targetVelocity.normalize()
			// targetVelocity *= targetSpeed

			// acceleration tries to get to the target velocity
			// steering.linear = targetVelocity - character.velocity
			// steering.linear /= timeToTarget

			// check if the acceleration is too fast
			// if steering.linear.length() > maxAcceleration
			// {
			//		steering.linear.normalize()
			//		steering.linear *= maxAcceleration
			// }
			
			// output the steering 
			// steering.angular = 0
			// return steering
		}
	*/

private:

};

#endif
