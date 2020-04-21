

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

// create ur own vector stuff
#include <math.h>
#include <vector>

struct BK_Vector2
{
	float xVal;
	float yVal;

	BK_Vector2()
	{
		xVal = 0;
		yVal = 0;
	}

	BK_Vector2(float newXVal, float newYVal)
	{
		xVal = newXVal;
		yVal = newYVal;
	}

	float magnitude() 
	{ 
		float mag;

		float xSquare = xVal * xVal;
		float ySquare = yVal * yVal;

		mag = sqrtf(xSquare + ySquare);

		return mag;
	}

	float Dot(BK_Vector2 other)
	{
		float result = (xVal * other.xVal) + (yVal * other.yVal);

		return result;
	}

	float sqrMagnitude()
	{
		return (xVal * xVal + yVal * yVal);
	}

	BK_Vector2 normalized()
	{
		BK_Vector2 normalVersion = BK_Vector2();

		float mag;

		float xSquare = xVal * xVal;
		float ySquare = yVal * yVal;

		mag = sqrtf(xSquare + ySquare);

		normalVersion.xVal = xVal / mag;
		normalVersion.yVal = yVal / mag;

		return normalVersion;
	}
};

bool operator==(BK_Vector2 left, BK_Vector2 right);

BK_Vector2 operator+(BK_Vector2 left, BK_Vector2 right);

BK_Vector2 operator+=(BK_Vector2 left, BK_Vector2 right);

BK_Vector2 operator-(BK_Vector2 left, BK_Vector2 right);

BK_Vector2 operator-=(BK_Vector2 left, BK_Vector2 right);

BK_Vector2 operator/(BK_Vector2 left, float right);

BK_Vector2 operator*(BK_Vector2 left, float right);

BK_Vector2 operator*(float left, BK_Vector2 right);


#endif // !MY_VECTOR_H

