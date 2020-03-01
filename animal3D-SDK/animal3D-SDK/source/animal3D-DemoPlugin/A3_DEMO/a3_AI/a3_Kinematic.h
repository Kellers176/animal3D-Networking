
#include "a3_SteeringOutput.h"
#include "animal3D-A3DM/a3math/a3sqrt.h"

#ifndef KINEMATIC_H
#define KINEMATIC_H


struct Kinematic
{
	float positionX;
	float positionY;

	float orientation;

	float velocityX;
	float velocityY;

	float rotation;

	void Update(SteeringOutput* steering, float maxSpeed, float deltaTime)
	{
		velocityX = steering->linear.x;
		velocityY = steering->linear.y;

		// check for speeding and clip
		float velocityMagnitude = a3sqrt(velocityX * velocityX + velocityY * velocityY);

		if (velocityMagnitude > maxSpeed)
		{
			velocityX /= velocityX;
			velocityX *= maxSpeed;

			velocityY /= velocityY;
			velocityY *= maxSpeed;
		}

		// update the position and orientation
		positionX += velocityX * deltaTime;
		positionY += velocityY * deltaTime;
		orientation += steering->angular * deltaTime;

	}

};

#endif