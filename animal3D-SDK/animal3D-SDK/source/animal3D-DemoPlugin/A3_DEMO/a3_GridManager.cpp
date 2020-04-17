#include "a3_GridManager.h"

#include <iostream>
#include <fstream>

using namespace std;

// constructor for the GridManager class
a3_GridManager::a3_GridManager(string filename)
{
	dataFile = filename;

	isInit = false;
	isCleanup = false;
}

// destructor for the GridManager class
a3_GridManager::~a3_GridManager()
{

}

// initializes the grid for a given level
void a3_GridManager::init(int displayWidth, int displayHeight)
{
	if (!isInit)
	{
		ifstream fin;
		int gridFiller = 0;
		size_t pos;
		string line;

		const string GRID_SCALER = "GRID SCALER";
		const string IMAGE_SCALER = "IMAGE SCALER";

		fin.open(dataFile);

		if (fin.fail())
		{
			std::cout << "data retrieval process failed" << endl;
			return;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			pos = line.find(GRID_SCALER);
			if (pos != string::npos)
			{
				fin >> gridScaler;
			}

			pos = line.find(IMAGE_SCALER);
			if (pos != string::npos)
			{
				fin >> imageScaler;
			}
		}

		fin.clear();
		fin.close();

		xVal = displayWidth / gridScaler;
		yVal = displayHeight / gridScaler;

		// populates the grid with "true" availability and "false" powerup values
		for (int i = 0; i < xVal; i++)
		{
			for (int j = 0; j < yVal; j++)
			{
				grid.push_back(a3_Grid(BK_Vector2(i, j), true, false));
				gridFiller++;
			}
		}
	}
}

// returns the availability of a certain space
bool a3_GridManager::checkAvailability(BK_Vector2 gridLoc)
{
	for (unsigned i = 0; i < grid.size(); i++)
	{
		if (grid.at(i).getGridPos() == gridLoc)
		{
			if (grid.at(i).getIsAvailable())
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}

	// if the space does not exist on the grid, exit the stage
	return false;
}

// changes whether or not a space is available
void a3_GridManager::changeAvailability(BK_Vector2 gridLoc, bool availability)
{
	for (unsigned i = 0; i < grid.size(); i++)
	{
		if (grid.at(i).getGridPos() == gridLoc)
		{
			grid.at(i).setIsAvailable(availability);
			break;
		}
	}
}

// returns whether or not a space contains a powerup
bool a3_GridManager::checkPowerup(BK_Vector2 gridLoc)
{
	for (unsigned i = 0; i < grid.size(); i++)
	{
		if (grid.at(i).getGridPos() == gridLoc)
		{
			if (grid.at(i).getPowerup())
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}

	// if the space does not exist, end the function gracefully
	return false;
}

// changes whether or not a space is available
void a3_GridManager::changePowerup(BK_Vector2 gridLoc, bool availability)
{
	for (unsigned i = 0; i < grid.size(); i++)
	{
		if (grid.at(i).getGridPos() == gridLoc)
		{
			grid.at(i).setPowerup(availability);
			break;
		}
	}
}

// returns the grid's scaling data
int a3_GridManager::getGridScale()
{
	return gridScaler;
}

// returns the image scaling data
float a3_GridManager::getImageScale()
{
	return imageScaler;
}

// returns the Grid's width
int a3_GridManager::getWidth()
{
	return xVal;
}

// returns the Grid's height
int a3_GridManager::getHeight()
{
	return yVal;
}

// returns the Grid's area
int a3_GridManager::getGridArea()
{
	return (xVal * yVal);
}