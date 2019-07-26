#include "GridCell.h"
#include "Grid.h"

void GridCell::JoinToVectorOfTiles(vector<Tile *> &output)
{
	output.insert(output.end(), this->tiles.begin(), this->tiles.end());
}

void GridCell::Render()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		CMap::GetInstance()->RenderTile(tiles[i]);
	}
}

GridCell::~GridCell()
{
}
