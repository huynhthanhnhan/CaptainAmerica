#pragma once
#include "Bullet.h"
#include  "Enemy.h"

class GreenSoldierBullet :
	public Bullet
{
public:
	GreenSoldierBullet(Enemy* enemy);
	void LoadResources();
	void Update(DWORD dt) override;
	void Render() override;

	void Reset() override;

	~GreenSoldierBullet();
};

