#pragma once
#include "Bullet.h"
#include  "Enemy.h"

class BossBullet :
	public Bullet
{
public:
	BossBullet(Enemy* enemy);
	void LoadResources();
	void Update(DWORD dt) override;
	void Render() override;

	void Reset() override;

	~BossBullet();
};

