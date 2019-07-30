#pragma once
#include "GameObject.h"
#include "Global.h" 
#include "GridCell.h"
#include "../GameObject/Captain/Captain.h"

#include <vector>

#include <fstream>
#include <string>

using namespace std;
class Enemy;
class Cell;

typedef vector<GridCell *> CellRow;
typedef vector<CellRow> CellMatrix;
class Grid {
private:
	static Grid * __instance;
	int width, height;

	CellMatrix cells;

	vector<Tile *> curTiles;

	vector<Tile *> CollisionTiles;

	Camera *camera;

	Captain * captain;


	std::vector<Enemy *> enemies;

	Grid();

	void LoadEnemies();

	void CreateEnemy(EnemyType type, int positionX, int positionY);

public:
	static Grid * GetInstance();
	void LoadCells();

	void GetCameraPosOnGrid(int &l, int &r, int &t, int &b);
	void GetCaptainPosOnGrid(int &l, int &r, int &t, int &b);

	vector<Tile *> GetCurTiles() { return this->curTiles; }
	vector<Tile *> GetCollisionTiles() { return this->CollisionTiles; }
	vector<Enemy* > GetEnemies() { return this->enemies; }
 
	void Update(DWORD dt);
	void Render();

	CellMatrix GetTile() { return this->cells; }

	static void SetNewGrid();
	~Grid();
};