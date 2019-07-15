#pragma once
#include "Constants.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "TiledMap.h"
#include "Grid.h"
#include "../Captain/Captain.h"

#include <chrono>

class Graphics;
class Keyboard;
class Grid;

class Game
{
	bool initialized = false;

	static Game * __instance;
	static HINSTANCE hInstance;
	HWND hWnd;									

	Keyboard * keyboard;
	Graphics * graphics;

	Captain* captain;

	TiledMap * tiledMap;
	Viewport * viewport;

	Grid * grid;

	Stage stage;
public:
	Stage GetStage() { return this->stage; }
	void SetStage(int stage) { this->stage = (Stage)stage; }

	void Init();
	HWND CreateGameWindow(HINSTANCE hInstance, int ScreenWidth, int ScreenHeight);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void LoadResources();


	void Update(DWORD dt);
	void Render();
	int Run();

	Captain* GetCaptain();

	TiledMap * GetTiledMap() { return tiledMap; }
	void SetTileMap(TiledMap * tiledMap) {
		this->tiledMap = tiledMap;
	}
	void SetGrid(Grid* grid)
	{
		this->grid = grid;
	}
	
	static float SweptAABB(Collider c1, Collider c2, float &normalx, float &normaly);
	static Game * GetInstance();
	~Game();
};


