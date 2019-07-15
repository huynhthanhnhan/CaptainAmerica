#pragma once
#include "Bullet.h"
#include  "Enemy.h"

class PinkWitchBullet :
	public Bullet
{
public:
	PinkWitchBullet(Enemy* enemy);
	void LoadResources();
	void Update(DWORD dt) override;
	void Render() override;

	void Reset() override;

	~PinkWitchBullet();
};


