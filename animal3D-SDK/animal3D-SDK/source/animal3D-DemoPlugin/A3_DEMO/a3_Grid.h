


#ifndef A3_GRID_H
#define A3_GRID_H

#include "BK_Vector.h"

class a3_Grid
{
public:
	a3_Grid(BK_Vector2 gridPos, bool isAvailable, bool powerUp);
	~a3_Grid();

	// mutators
	void setIsAvailable(bool availability);
	void setPowerup(bool containsPowerup);

	// accessors
	BK_Vector2 getGridPos();
	bool getIsAvailable();
	bool getPowerup();

private:
	BK_Vector2 mGridPos;
	bool mIsAvailable;
	bool mPowerup;
};
#endif // !A3_GRID_H

