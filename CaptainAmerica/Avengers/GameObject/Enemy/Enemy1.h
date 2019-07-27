#pragma once
#include "Enemy.h"
#include "../../GameFramework/Global.h"
#include "../../GameFramework/GameObject.h"
#include "../../GameFramework/Grid.h"
#include "Enemy1Bullet.h"

class Enemy1 : public Enemy
{
	float timeToAction = 0;

	float timeToFire = 100;

	float countTimeToFire = 0;

	Enemy1Bullet * bullet;
public:
	Enemy1();
	void LoadResource();
	void Update(DWORD dt) ;
	void Render();
};