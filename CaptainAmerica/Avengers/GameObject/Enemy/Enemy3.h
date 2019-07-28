#pragma once
#include "Enemy.h"
#include "../../GameFramework/Global.h"
#include "../../GameFramework/GameObject.h"
#include "../../GameFramework/Grid.h"
#include "Enemy3Bullet.h"

class Enemy3 : public Enemy
{
	float timeToAction = 0;

	float timeToFire = 100;

	float countTimeToFire = 0;

	Enemy3Bullet * bullet;
public:
	Enemy3();
	void LoadResource();
	void Update(DWORD dt);
	void Render();
};