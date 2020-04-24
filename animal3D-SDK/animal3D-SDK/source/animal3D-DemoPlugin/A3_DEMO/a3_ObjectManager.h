

#ifndef A3_OBJECT_MANAGER_H
#define A3_OBJECT_MANAGER_H

#include <string>
#include <vector>
#include "a3_Object.h"

class a3_ObjectManager
{
public:
	a3_ObjectManager(){}
	~a3_ObjectManager(){}

	void a3_UpdateAllObjects(float deltaTime);
	void a3_RenderAllObjects(a3_TextRenderer* newRenderer);

	void a3_CreateNewObject(a3byte** newText, BK_Vector2 newPos,int posInArray, bool isStatic, bool canMoveToObject, bool isTurnSpot, bool isPower);

	void a3_CreateNewDynamicObject(a3byte** newText, BK_Vector2 newPos,int currentNode);
	void a3_CreateNewGhostObject(a3byte** newText, BK_Vector2 newPos, int currentNode);

	void a3_CreateNewObjectWithID(int newID);

	a3_Object* a3_GetObjectInPos(int objPos);
	// gets the dynamic object
	a3_Object* a3_GetObjectFromID(int unitID);

	void a3_SetObjectPos(int objID, BK_Vector2 newPos);
	void a3_SetObjectVel(int objID, BK_Vector2 newPos);
	void a3_SetObjectRotation(int objID, float newRotation);

	int GetSize() { return (int)listOfObjects.size(); }

	void CreateLevel(std::string fileName, int numberOfPlayers);
	void ResetAllObjects();

	void a3_SetPlayerDirection(int playerID, Direction newDir);

	void a3_SetScore(int newScore) { score = newScore; }
	int a3_GetScore() { return score; }

	void a3_PowerGained();
	void a3_EatenPip(int pipPos);

private:
	std::vector<a3_Object*> listOfObjects;
	std::vector<a3_Object*> listOfDynamicObjects; // actually player but i dont want to rename
	std::vector<a3_Object*> listOfGhostObjects;

	float ghostTimer = 0;
	float edibleTimer = 0;

	int lives = 3;
	int score = 0;
};

#endif

// 39x23 grid for the game

/*

Static objects:
'#' - wall and cannot be cannot be moved onto
'.' - pip and can be moved onto
' ' - AKA space and can be moved onto
'O' - is mega pip and can be moved onto and makes the text blue

Dynamic:
'@' - is pacman and will either be Green or (dark plain as day non pink) Purple

'B' - is Blinky (will be red) ghost
'I' - inky (will be cyan)
'P' - pinky (will be pink)
'C' - clyde (will be orange)

*/