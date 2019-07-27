#pragma once
#include "Enemy.h"
#include "../../GameFramework/Global.h"
#include "../../GameFramework/GameObject.h"
#include "../../GameFramework/Grid.h"

class Enemy1 : public Enemy
{
	float timeToAction = 0;
public:
	Enemy1();
	void LoadResource();
	void Update(DWORD dt) ;
	void Render();
};