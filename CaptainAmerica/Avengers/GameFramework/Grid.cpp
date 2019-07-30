#include"Grid.h"
#include "Game.h"

Grid *Grid::__instance = NULL;

Grid::Grid()
{
	curTiles.clear();

	this->width = (int)(Game::GetInstance()->GetMap()->GetWidth() / GRID_SIZE) + 2;
	this->height = (int)(Game::GetInstance()->GetMap()->GetHeight() / GRID_SIZE) + 2;

	for (int i = 0; i < height; i++)
	{
		CellRow curRow;
		for (int j = 0; j < width; j++)
		{
			GridCell *curCell = new GridCell(j, i);
			curRow.push_back(curCell);
		}
		cells.push_back(curRow);
	}
	LoadCells();

	this->camera = Camera::GetInstance();
	this->captain = Captain::GetInstance();

	LoadEnemies();
}

void Grid::LoadCells()
{
	vector< vector<Tile>> &mapMatrix = Game::GetInstance()->GetMap()->GetMapMatrix();
	for (int i = 0; i < mapMatrix.size(); i++)
	{
		for (int j = 0; j < mapMatrix[i].size(); j++)
		{
			//Tim vi tri o chua tile
			int cellX = (int)mapMatrix[i][j].x / GRID_SIZE;
			int cellY = (int) (mapMatrix[i][j].y % GRID_SIZE == 0 ? mapMatrix[i][j].y / GRID_SIZE - 1 : mapMatrix[i][j].y / GRID_SIZE);

			Tile *tmp = &mapMatrix[i][j];
			cells[cellY][cellX]->AddTile(tmp); // do cells có kiểu là mảng các GridCell (GridCell là mảng các cellRow trên dòng) nên truyền i của mảng GridCel trước

			if (mapMatrix[i][j].type == ObjectType::BRICK)
			{
				CollisionTiles.push_back(tmp);
			}
		}
	}
}

void Grid::LoadEnemies()
{
	enemies.clear();
	EnemyLocation* enemiesLocation = LoadTXT::Instance()->LoadEnemiesLocation((char*)"Resources\\Enemy\\EnemiesLocation.txt");
	for (int i = 0;i < 3;i++)
	{
		CreateEnemy((EnemyType)enemiesLocation[i].type, enemiesLocation[i].positionX, enemiesLocation[i].positionY);
	}
}

void Grid::CreateEnemy(EnemyType type, int positionX, int positionY)
{
	Enemy* enemy = NULL;
	switch (type)
	{
	case ENEMY1:
		enemy = new Enemy1(positionX,positionY);
		break;
	case ENEMY2:
		enemy = new Enemy2(positionX, positionY);
		break;
	case ENEMY3:
		enemy = new Enemy3(positionX, positionY);
		break;
	default:
		break;
	}
	if (enemy != NULL)
	{
		enemies.push_back(enemy);
	}
}

void Grid::GetCaptainPosOnGrid(int &l, int &r, int &t, int &b) // lấy vị trí captain trên grid
{
	RECT rect = captain->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}

void Grid::GetCameraPosOnGrid(int &l, int &r, int &t, int &b) {
	RECT rect = camera->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}

void Grid::Update(DWORD dt)
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);

	//Update captain
	//curTiles.clear();

	//for (size_t i = 0; i < cells.size(); i++)
	//{
	//	for (size_t j = 0; j < cells[i].size(); j++)
	//	{
	//		cells[i][j]->clear();
	//	}
	//}

	for (size_t i = 0; i < enemies.size();i++)
	{
		enemies[i]->Update(dt);
	}

	int captainLCell, captainRCell, captainTCell, captainBCell;

	this->GetCaptainPosOnGrid(captainLCell, captainRCell, captainTCell, captainBCell);

	for (int i = captainBCell; i <= captainTCell; i++)
	{
		for (int j = captainLCell; j <= captainRCell; j++)
		{
			cells[i][j]->JoinToVectorOfTiles(curTiles);
		}
	}

	captain->Update(dt);
}
void Grid::Render()
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);
	curTiles.clear();

	for (int i = bCell; i <= tCell; i++)
	{
		for (int j = lCell; j <= rCell; j++)
		{
			cells[i][j]->Render();
		}
	}

	for (size_t i = 0; i < enemies.size();i++)
	{
		enemies[i]->Render();
	}

	captain->Render();
}

Grid *Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}

void Grid::SetNewGrid()
{
	__instance = NULL;
	__instance = new Grid();
}

Grid::~Grid() {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			if (cells[i][j] != NULL)
				delete cells[i][j];
		}
}