#include"Grid.h"
#include "Game.h"

Grid * Grid::__instance = NULL;

Grid::Grid()
{
	curTiles.clear();

	//khoi tao danh sach cac o trong
	this->width = (int)(Game::GetInstance()->GetTiledMap()->GetWidth() / 64) + 2;
	this->height = (int)(Game::GetInstance()->GetTiledMap()->GetHeight() / 64) + 2;

	for (int i = 0; i < height; i++)
	{
		CellRow curRow;
		for (int j = 0; j < width; j++)
		{
			GridCell * curCell = new GridCell(j, i);
			curRow.push_back(curCell);
		}
		cells.push_back(curRow);
	}
	LoadCells();

	//Luu viewport
	this->viewport = Viewport::GetInstance();
	//Lưu ninja
	this->ninja = Ninja::GetInstance();

	ReadEnemiesFromFIle(Game::GetInstance()->GetStage());
}
void Grid::LoadEnemy(LPCWSTR filePath, Stage gamestage)
{
	ifstream tilesInfo;
	DebugOut(L"filepath: %s\n", filePath);
	tilesInfo.open(filePath);

	int mapheight = TiledMap::GetInstance()->GetHeight();

	string line;
	int token;

	int Id = 0;
	if (tilesInfo.is_open())
	{
		while (getline(tilesInfo, line))
		{
			size_t pos = 0;
			int rowNum = 0 , posx = 0, posy = 0 , type = 0;
			bool isleft = false;
			int GameItem = -1;

			int min_posx = 0 , max_posx = 0;

			while ((pos = line.find(" ")) != string::npos)
			{
				token = stoi(line.substr(0, pos));
				if (rowNum == Column::Type)
				{
					type = token;
				}
				else if (rowNum == Column::PosX) posx = token;
				else if (rowNum == Column::Direction)
				{
					if (token == 0)
					{
						isleft = true;
					}
					else if (token == 1) isleft = false;
				}
				else if (rowNum == Column::PosY)
				{
					if (type == YELLOWSOLDIER)
					{
						posy = mapheight - token + 50;
					}
					else
					{
						posy = mapheight - token;
					}
				}
				else if (rowNum == Column::ItemType)
				{
					GameItem = token;
				}
				else if (rowNum == Column::MinPosX)
				{
					min_posx = token;
				}
				else if (rowNum == Column::MaxPosX)
				{
					max_posx = token;
				}
				line.erase(0, pos + 1);
				rowNum++;
			}

			CreateEnemy(Id,type, posx, posy,isleft, GameItem, min_posx, max_posx);
			Id++;
		}
		tilesInfo.close();
	}
}
void Grid::CreateEnemy(int Id , int type , int posx , int posy , bool isLeft, int GameItem, float min_posX , float max_posX)
{
	Enemy * enemy = NULL;

	switch (type)
	{
	case YELLOWSOLDIER:
		enemy = new YellowSolider(posx, posy);
		break;
	case REDBIRD:
		enemy = new RedBird(posx, posy);
		enemy->SetItemType(GameItem);
		break;
	case BROWNBIRD:
		enemy = new BrownBird(posx, posy);
		break;
	case YELLOWPANTHER:
		enemy = new YellowPanther(posx, posy);	
		break;
	case PINKWITCH:
	{
		enemy = new PinkWitch(posx, posy);
		auto bullet_pw = new PinkWitchBullet(enemy);
		AddBullet(bullet_pw);
		break;
	}
	case GREENSOLDIER:
	{
		enemy = new GreenSolider(posx, posy);
		auto bullet_gs = new GreenSoldierBullet(enemy);
		AddBullet(bullet_gs);
		break;
	}

	case BLOODYBIRD:
		enemy = new BloodyBird(posx, posy);
		enemy->SetItemType(GameItem);
		break;
	case GREENCANONSOLDIER:
	{
		enemy = new GreenCanonSoldier(posx, posy);
		auto bullet = new GreenCannonSoldierBullet(enemy);
		AddBullet(bullet);
		break;
	}
	case GREENRUNNINGSOLDIER:
		enemy = new GreenRunningSoldier(posx, posy);
		break;
	case BOSS:
	{
		enemy = new Boss(posx, posy);
		auto bossbullet1 = new BossBullet(enemy);

		auto bossbullet2 = new BossBullet(enemy);
		bossbullet2->SetPositionY(bossbullet1->GetPositionY() - 30);
		bossbullet2->SetPositionX(bossbullet1->GetPositionX());

		auto bossbullet3= new BossBullet(enemy);
		bossbullet3->SetPositionY(bossbullet1->GetPositionY() - 50);
		bossbullet3->SetPositionX(bossbullet1->GetPositionX());

		AddBullet(bossbullet1);
		AddBullet(bossbullet2);
		AddBullet(bossbullet3);
		break;
	}
	default:
		break;
	}
	enemy->SetId(Id);
	//enemy->SetMovingDistance(distance);
	enemy->SetBoudary(min_posX, max_posX);
	if (enemy != NULL)
	{
		enemy->Setleft(isLeft);

		int cellX = POSXTOCELL(posx);
		int cellY = POSYTOCELL(posy);

		cells[cellY][cellX]->AddEnemy(enemy);
		enemies.push_back(enemy);
	}
}


void Grid::LoadCells()
{
	Matrix &tiledMapMatrix = Game::GetInstance()->GetTiledMap()->GetMatrix();
	for (int i = 0; i < tiledMapMatrix.size(); i++)
	{
		for (int j = 0; j < tiledMapMatrix[i].size(); j++)
		{
			//Tim vi tri o chua tile
			int cellX = POSXTOCELL(tiledMapMatrix[i][j].x);
			int cellY = POSYTOCELL(tiledMapMatrix[i][j].y);

			Tile * dummyPtr = &tiledMapMatrix[i][j];
			cells[cellY][cellX]->AddTile(dummyPtr);

			if (tiledMapMatrix[i][j].type == ObjectType::BRICK)
			{
				CollisionTiles.push_back(dummyPtr);
			}
		}
	}
}

void Grid::GetCameraPosOnGrid(int &l, int &r, int &t, int &b) {
	RECT rect = viewport->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}

void Grid::GetNinjaPosOnGrid(int &l, int &r, int &t, int &b)
{
	RECT rect = ninja->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}
void Grid::ReadEnemiesFromFIle(Stage GameStage)
{
	LPCWSTR filePath = L"";
	if (GameStage == Stage::STAGE_31)
	{
		enemies.clear();
		filePath = ENEMIES_MAP_31;
	}
	else if (GameStage == Stage::STAGE_32)
	{
		enemies.clear();
		filePath = ENEMIES_MAP_32;
	}
	else if (GameStage == Stage::STAGE_BOSS)
	{
		enemies.clear();
		filePath = ENEMIES_MAP_BOSS;
	}
	LoadEnemy(filePath, GameStage);
}
void Grid::Update(DWORD dt)
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);

	//Update ninja
	curTiles.clear();
	curEnemies.clear();

	for (size_t i = 0; i < cells.size(); i++)
	{
		for (size_t j = 0; j < cells[i].size(); j++)
		{
			cells[i][j]->clear();
		}
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetPositionY() < 50)
		{
			enemies.erase(enemies.begin() + i);
		}
		else
		{
			enemies[i]->Update(dt);
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		int cellX = POSXTOCELL((int)enemies[i]->GetPositionX());
		int cellY = POSYTOCELL((int)enemies[i]->GetPositionY());

		if (enemies[i]->Isdeath() == false && enemies[i]->IsActive() == true)
		{
			cells[cellY][cellX]->AddEnemy(enemies[i]);
		}
	}

	int ninjaLCell, ninjaRCell, ninjaTCell, ninjaBCell;

	this->GetNinjaPosOnGrid(ninjaLCell, ninjaRCell, ninjaTCell, ninjaBCell);

	for (int i = ninjaBCell; i <= ninjaTCell; i++)
	{
		if (ninjaLCell - 2 >= 0)
		{
			if (ninjaRCell + 5 < 34 && Game::GetInstance()->GetStage() != Stage::STAGE_BOSS)
			{
				for (int j = ninjaLCell - 2; j <= ninjaRCell + 5; j++)
				{
					cells[i][j]->InsertEnemies(curEnemies);
				}
				for (int j = ninjaLCell; j <= ninjaRCell; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
				}
			}
			else if (ninjaRCell + 5 >= 34 && Game::GetInstance()->GetStage() != Stage::STAGE_BOSS)
			{
				for (int j = ninjaLCell - 2; j <= ninjaRCell; j++)
				{
					cells[i][j]->InsertEnemies(curEnemies);
				}
				for (int j = ninjaLCell; j <= ninjaRCell; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
				}
			}
			else if (Game::GetInstance()->GetStage() == Stage::STAGE_BOSS)
			{
				for (int j = ninjaLCell; j <= ninjaRCell; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
					cells[i][j]->InsertEnemies(curEnemies);
				}
			}
		}
		else {
			if (ninjaRCell + 5 < 34)
			{
				for (int j = ninjaLCell; j <= ninjaRCell + 5; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
					cells[i][j]->InsertEnemies(curEnemies);
				}
			}
		}
	}

	ninja->Update(dt);

	for (size_t i = 0; i < deathanimations.size(); i++)
	{
		if (deathanimations[i]->IsActive() == true || deathanimations[i]->CheckStatus()==true)
		{
			deathanimations[i]->Update(dt);
		}
		else
		{
			deathanimations.erase(deathanimations.begin() + i);
		}
	}

	for (size_t i = 0; i < gameitems.size(); i++)
	{
		if (gameitems[i]->IsActive() == true)
		{
			gameitems[i]->Update(dt);
		}
		else
		{
			gameitems.erase(gameitems.begin() + i);
		}
	}

	for (size_t i = 0; i < enemiesbullet.size(); i++)
	{
		enemiesbullet[i]->Update(dt);
	}
}
void Grid::Render()
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);
	curTiles.clear();
	curEnemies.clear();

	for (int i = bCell; i <= tCell; i++)
	{
		for (int j = lCell; j <= rCell; j++)
		{
			cells[i][j]->Render();
		}
	}

	ninja->Render();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsActive() == true)
		{
			enemies[i]->Render();
		}
	}

	for (size_t i = 0; i < deathanimations.size(); i++)
	{
		if (deathanimations[i]->IsActive() == true)
		{
			deathanimations[i]->Render();
		}
	}
	for (size_t i = 0; i < gameitems.size(); i++)	
	{
		if (gameitems[i]->IsActive() == true)
		{
			gameitems[i]->Render();
		}
	}

	for (size_t i = 0; i < enemiesbullet.size(); i++)
	{
		if (enemiesbullet[i]->IsActive() == true)
		{
			enemiesbullet[i]->Render();
		}
	}
}

void Grid::DeleteBullet(Enemy * enemy)
{
	for (size_t i = 0; i < enemiesbullet.size(); i++)
	{
		if (enemiesbullet[i]->GetEnemy()->GetId() == enemy->GetId())
		{
			this->enemiesbullet.erase(enemiesbullet.begin() + i);
			return;
		}
	}
}

void Grid::DeleteBossBullet()
{
	for (size_t i = 0; i < enemiesbullet.size(); i++)
	{
		if (enemiesbullet[i]->GetBulletType() == BulletType::BOSS_BULLET && enemiesbullet[i]->IsActive() == false)
		{
			enemiesbullet[i]->Reset();
		}
	}
}
int Grid::GetEnemyIndexById(int Id)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetId() == Id) return i;
	}
	return -1;
}

int Grid::GetGameItemIndexById(int Id)
{
	for (size_t i = 0; i < gameitems.size(); i++)
	{
		if (gameitems[i]->GetId() == Id)
		{
			return i;
		}
	}
	return -1;
}

Grid * Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}
