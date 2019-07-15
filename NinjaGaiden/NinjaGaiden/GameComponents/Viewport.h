#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "Constants.h"

class GameObject;
class Enemy;
class Viewport
{
	static Viewport * __instance;
	Viewport();
	int width;
	int height;
	int x = 0;
	int y = MAP_HEIGHT;
public:
	static Viewport * GetInstance();
	~Viewport();

	RECT GetRect();

	void Reset();
	void Update(DWORD dt);
	bool IsEnemyInCamera(Enemy* enemy);
	bool IsObjectInCamera(GameObject* gameobject);
	void SetRenderData(D3DXVECTOR2 &center, D3DXVECTOR2 &translate, D3DXVECTOR2 &scaling);
};