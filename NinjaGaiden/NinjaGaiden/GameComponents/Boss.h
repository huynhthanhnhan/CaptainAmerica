#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Enemy.h"
#include "BossBullet.h"

class Boss :public Enemy
{
	int count;
	static Boss * __instance;
	
public:
	bool shootBullet=true;

	Boss();
	Boss(float posx, float posy);
	void LoadResources();
	void Idle();
	void Walk();

	int GetStamina() { return this->stamina; }

	bool checkloc = true;

	bool initloc = true;
	//Hàm cập nhật
	static Boss * GetInstance();
	void ShootBullet();
	void StopShootBullet();
	void Update(DWORD dt) override;
	bool GetCheckBullet() { return this->shootBullet; }
	//Hàm render
	void Render() override;
};

