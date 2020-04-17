#include "BK_Vector.h"

bool operator==(BK_Vector2 left, BK_Vector2 right)
{
	if (left.xVal == right.xVal && left.yVal == right.yVal)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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