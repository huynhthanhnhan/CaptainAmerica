#pragma once

#include <vector>
#include "GameObject.h"
#include "Map.h"

class GridCell
{
private:
	vector<Tile *> tiles;

	int iX;
	int iY;
public:
	GridCell(int iX, int iY) { this->iX = iX; this->iY = iY; }

	void AddTile(Tile * tile) { this->tiles.push_back(tile); }
	int GetPositionX() { return iX * GRID_SIZE; }
	int GetPositionY() { return (iY + 1) * GRID_SIZE; }

	void JoinToVectorOfTiles(vector<Tile *> &output);
	void Render();
	~GridCell();
};

