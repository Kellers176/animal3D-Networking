

#ifndef OBJECT_INFO_H
#define OBJECT_INFO_H

#pragma pack(push, 1)
struct MoveInputData
{
	unsigned char typeId;
	int objType;
	a3_KeyboardKey input;
};
#pragma pack(push)

#pragma pack(push, 1)
struct ObjectPosInfo
{
	unsigned char typeId;
	int objType;
	float xMoveVal;
	float yMoveVal;
	float zMoveVal;
};
#pragma pack(push)

#endif