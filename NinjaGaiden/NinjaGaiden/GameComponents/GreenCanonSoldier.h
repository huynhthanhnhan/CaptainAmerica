#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Enemy.h"
#include "GreenCannonSoldierBullet.h"

class GreenCanonSoldier :public Enemy
{
public:
	GreenCanonSoldier();
	GreenCanonSoldier(float posx, float posy);
	void LoadResources();
	void Idle();
	void Walk();
	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;
};

