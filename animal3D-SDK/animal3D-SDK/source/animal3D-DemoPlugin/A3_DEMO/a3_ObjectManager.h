

#ifndef A3_OBJECT_MANAGER_H
#define A3_OBJECT_MANAGER_H

#include <vector>

class a3_ObjectManager
{
public:
	a3_ObjectManager();

	~a3_ObjectManager();


private:
	std::vector<a3_Object> listOfObjects;
};

#endif