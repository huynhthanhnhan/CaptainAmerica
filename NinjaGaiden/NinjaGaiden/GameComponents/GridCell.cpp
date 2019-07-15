#include "GridCell.h"
#include "Grid.h"


void GridCell::InsertTiles(vector<Tile *> &output)
{
	output.insert(output.end(), this->tiles.begin(), this->tiles.end());
}

void GridCell::InsertEnemies(vector<Enemy *> &output)
{
	output.insert(output.end(), this->enemies.begin(), this->enemies.end());
}

void GridCell::Update(DWORD dt)
{
	return;
}
void GridCell::Render()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		TiledMap::GetInstance()->RenderTile(tiles[i]);
	}
}

GridCell::~GridCell()
{
}
