

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

	float magnitude() { return sqrt(xVal * xVal + yVal * yVal); }

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
		float newMag = magnitude();

		normalVersion.xVal = xVal / newMag;
		normalVersion.yVal = yVal / newMag;

		return normalVersion;
	}
};

BK_Vector2 operator+(BK_Vector2 left, BK_Vector2 right)
{
	BK_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal + right.xVal;
	newVec2.yVal = left.yVal + right.yVal;

	return newVec2;
}

BK_Vector2 operator+=(BK_Vector2 left, BK_Vector2 right)
{
	BK_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal + right.xVal;
	newVec2.yVal = left.yVal + right.yVal;

	return newVec2;
}

BK_Vector2 operator-(BK_Vector2 left, BK_Vector2 right)
{
	BK_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal - right.xVal;
	newVec2.yVal = left.yVal - right.yVal;

	return newVec2;
}

BK_Vector2 operator-=(BK_Vector2 left, BK_Vector2 right)
{
	BK_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal - right.xVal;
	newVec2.yVal = left.yVal - right.yVal;

	return newVec2;
}

BK_Vector2 operator/(BK_Vector2 left, float right)
{
	BK_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal / right;
	newVec2.yVal = left.yVal / right;

	return newVec2;
}

BK_Vector2 operator*(BK_Vector2 left, float right)
{
	BK_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal * right;
	newVec2.yVal = left.yVal * right;

	return newVec2;
}

BK_Vector2 operator*(float left, BK_Vector2 right)
{
	BK_Vector2 newVec2(0, 0);

	newVec2.xVal = right.xVal * left;
	newVec2.yVal = right.yVal * left;

	return newVec2;
}


#endif // !MY_VECTOR_H

