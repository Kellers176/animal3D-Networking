
#include "a3_Grid.h"

// constructor for the Grid class
a3_Grid::a3_Grid(BK_Vector2 gridPos, bool isAvailable, bool powerUp)
{
	mGridPos = gridPos;
	mIsAvailable = isAvailable;
	mPowerup = powerUp;
}

// destructor for the Grid class
a3_Grid::~a3_Grid()
{

}

// sets the availability
void a3_Grid::setIsAvailable(bool availability)
{
	mIsAvailable = availability;
}

// sets whether or not a space contains a powerup
void a3_Grid::setPowerup(bool containsPowerup)
{
	mPowerup = containsPowerup;
}

// returns the grid position
BK_Vector2 a3_Grid::getGridPos()
{
	return mGridPos;
}

// returns the availability
bool a3_Grid::getIsAvailable()
{
	return mIsAvailable;
}

// returns whether or not there is a powerup
bool a3_Grid::getPowerup()
{
	return mPowerup;
}