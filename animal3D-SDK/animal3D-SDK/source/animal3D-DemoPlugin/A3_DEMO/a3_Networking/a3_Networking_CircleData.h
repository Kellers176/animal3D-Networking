
#include <vector>

#ifndef CIRCLE_DATA_H
#define CIRCLE_DATA_H

struct Color
{
	int red;
	int green;
	int blue;
	int alpha;
};

#pragma pack(push,1)
struct CircleData
{
	int mouseXPos;
	int mouseYPos;
	int sizeCircle;

	Color circleColor;

};
#pragma pack(pop)

#endif
