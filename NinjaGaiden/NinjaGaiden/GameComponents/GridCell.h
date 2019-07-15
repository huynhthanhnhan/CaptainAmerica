#pragma once

#include <vector>
#include "GameObject.h"
#include "TiledMap.h"

class GridCell
{
private:
	vector<Enemy *> enemies;
	vector<Tile *> tiles;

	int iX;
	int iY;
public:
	GridCell(int iX, int iY) { this->iX = iX; this->iY = iY; }

	void AddTile(Tile * tile) { this->tiles.push_back(tile); }
	void AddEnemy(Enemy * enemy) { this->enemies.push_back(enemy); }
	void clear() { enemies.clear(); }
	int GetPositionX() { return iX * GRID_SIZE; }
	int GetPositionY() { return (iY + 1) * GRID_SIZE; }

	void InsertTiles(vector<Tile *> &output);
	void InsertEnemies(vector<Enemy *> &output);

	void Update(DWORD dt);
	void Render();
	~GridCell();
};

