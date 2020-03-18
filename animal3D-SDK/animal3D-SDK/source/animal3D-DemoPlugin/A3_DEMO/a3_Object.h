

#ifndef A3_OBJECT_H
#define A3_OBJECT_H

#include "animal3D-A3DG/a3graphics/a3_TextRenderer.h"

struct ObjKinData
{
	float posX, posY;

};

class a3_Object
{
public:
	a3_Object();
	~a3_Object();

	void a3_RenderObject();

private:
	a3_TextRenderer objectRenderer[1];
	const a3byte* objectShape[1];
	ObjKinData kinData;
};


#endif // A3_OBJECT_H
