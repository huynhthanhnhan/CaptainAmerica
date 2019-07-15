#pragma once
#include "GameObject.h"
#include "Constants.h" 
#include "GridCell.h"
#include "Ninja.h"
#include "DeathAnimation.h"
#include "GameItem.h"
#include "Bullet.h"

#include <vector>

#include <fstream>
#include <string>

#define POSTOCELL(K) (int)(K/GRID_SIZE);
#define POSXTOCELL(K) (int)(K/GRID_SIZE);
#define POSYTOCELL(K) (int)(K % GRID_SIZE == 0 ? K/GRID_SIZE - 1 : K/GRID_SIZE);

using namespace std;

class Cell;

typedef vector<GridCell *> CellRow;
typedef vector<CellRow> CellMatrix;
class Grid {
private:
	static Grid * __instance;
	int width, height;

	CellMatrix cells;

	vector<Tile *> curTiles;
	vector<Enemy *> curEnemies;

	vector<Tile *> CollisionTiles;
	vector<Enemy* > enemies;

	vector<Bullet* > enemiesbullet;

	vector<GameItem* > gameitems;

	vector<DeathAnimation* > deathanimations;


	Viewport *viewport;
	Ninja * ninja;

	void LoadEnemy(LPCWSTR filePath, Stage gamestage);

	void CreateEnemy(int Id , int type, int posx, int posy, bool isLeft,int GameItem, float min_posX, float max_posX);
	Grid();

public:
	static Grid * GetInstance();
	void LoadCells();

	void GetCameraPosOnGrid(int &l, int &r, int &t, int &b);
	void GetNinjaPosOnGrid(int &l, int &r, int &t, int &b);
	vector<Bullet*> GetEnemyBullet() { return enemiesbullet; }

	vector<Tile *> GetCurTiles() { return this->curTiles; }
	vector<Tile *> GetCollisionTiles() { return this->CollisionTiles; }
	vector<Enemy*> GetEnemies() { return curEnemies; }
	vector<Enemy*> GetAllEnemies() { return enemies; }
	vector<GameItem*> GetGameItem() { return gameitems; }
 
	void ReadEnemiesFromFIle(Stage GameStage);
	void Update(DWORD dt);
	void Render();

	CellMatrix GetTile() { return this->cells; }

	void AddEnemy(Enemy* enemy)
	{
		enemies.push_back(enemy);
	}
	void DeleteEnemy(int pos)
	{
		this->enemies.erase(enemies.begin() + pos);
	}

	void AddDeathAnimation(DeathAnimation* animation) { this->deathanimations.push_back(animation); }

	void AddGameItem(GameItem* gameitem) { this->gameitems.push_back(gameitem); }

	void AddBullet(Bullet* enemybullet) { this->enemiesbullet.push_back(enemybullet); }
	void DeleteBullet(Enemy * enemy);

	int GetEnemyIndexById(int Id);
	int GetGameItemIndexById(int Id);

	void DeleteGameItem(int pos) { this->gameitems.erase(gameitems.begin() + pos); }

	void DeleteBossBullet();

	static void SetNewGrid()
	{
		__instance = NULL;
		__instance = new Grid();
	}
	~Grid() {
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				if (cells[i][j] != NULL)
					delete cells[i][j];
			}
	}
};