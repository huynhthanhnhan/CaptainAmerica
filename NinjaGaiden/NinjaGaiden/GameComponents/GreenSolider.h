#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Enemy.h"
#include "GreenSoldierBullet.h"

class GreenSolider :public Enemy
{
private:
	GreenSoldierBullet* bullet_gs;
public:
	GreenSolider();
	GreenSolider(float posx, float posy);
	void LoadResources();
	void Idle();
	void Walk();
	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;
};
