
#include "a3_Kinematic.h"


void Kinematic::Update( float maxSpeed, float deltaTime)
{
	// update the position and orientation
	position += velocity * deltaTime;
	orientation += steering.angular * deltaTime;
	
	// check for speeding and clip
	float velocityMagnitude = a3sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	
	if (velocityMagnitude > maxSpeed)
	{
		velocity = velocity / velocityMagnitude;
		velocity *= maxSpeed;
	}
}
