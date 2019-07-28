#pragma once
#include "Enemy.h"
#include "../../GameFramework/Global.h"
#include "../../GameFramework/GameObject.h"
#include "../../GameFramework/Grid.h"
#include "Enemy2Bullet.h"

class Enemy2 : public Enemy
{
	float timeToAction = 0;

	float timeToFire = 100;

	float countTimeToFire = 0;

	Enemy2Bullet * bullet;
public:
	Enemy2();
	void LoadResource();
	void Update(DWORD dt);
	void Render();
};