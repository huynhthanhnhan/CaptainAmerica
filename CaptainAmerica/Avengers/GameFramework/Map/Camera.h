#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "../Global.h"

class GameObject;
class Camera
{
	static Camera * __instance;
	Camera();
	int width;
	int height;
	int x = 0;
	int y = MAP_HEIGHT;
public:
	static Camera * GetInstance();
	~Camera();

	RECT GetRect();

	void Reset();
	void Update(DWORD dt);
	bool IsObjectInCamera(GameObject* gameobject);
	void SetRenderData(D3DXVECTOR2 &center, D3DXVECTOR2 &translate, D3DXVECTOR2 &scaling);
};