


#ifndef A3_GRID_MANAGER_H
#define A3_GRID_MANAGER_H

#include "BK_Vector.h"
#include "a3_Grid.h"

#include <vector>
#include <string>

class a3_GridManager 
{
public:
	a3_GridManager(std::string filename);
	~a3_GridManager();

	void init(int displayWidth, int displayHeight);

	// accessors
	int getGridScale();
	float getImageScale();
	int getWidth();
	int getHeight();
	int getGridArea();

	// checks or changes a space's availability
	bool checkAvailability(BK_Vector2 gridPos);
	void changeAvailability(BK_Vector2 gridPos, bool availability);
	bool checkPowerup(BK_Vector2 gridPos);
	void changePowerup(BK_Vector2 gridPos, bool containsPowerup);

private:
	std::vector<a3_Grid> grid;

	std::string dataFile;

	// information used to determine grid size
	int xVal;
	int yVal;

	int gridScaler;
	float imageScaler;

	bool isInit;
	bool isCleanup;
};

#endif // !A3_GRID_MANAGER_H