

#ifndef SEEK_H
#define SEEK_H

class SeekBehavior
{
public:
	// holds the kinematic data for the character and target
	// target

	// holds the maximum acceleration of the character
	// maxAcceleration

	// returns the desired steering output
	// ref getSteering();

	// create the structure to hold our output
	// steering = new SteeringOutput();

	// get the direction to the target
	// steering.linear = target.position - character.position

	// give full accleration along this direction
	// steering.linear.normalize();
	// steering *= maxAcceleration;

	// output the steering 
	// steering.angular = 0; return steering

private:

};


#endif