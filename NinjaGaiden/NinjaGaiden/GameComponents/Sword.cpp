#include "Sword.h"

Sword * Sword::__instance = NULL;
Sword::Sword()
{
	width = NINJA_SPRITE_WIDTH + 10;
	height = NINJA_SPRITE_HEIGHT / 3;

	vy = 0;
	attacktime = ATTACKTIME;
	damage = 500;
}


Sword * Sword::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Sword();
	}
	return __instance;
}

void Sword::ResetAttackTime()
{
	this->attacktime = ATTACKTIME;
}

void Sword::ResetCollider()
{
	this->collider.x = 0;
	this->collider.x = 0;
	this->vx = 0;
	this->collider.vy = 0;
	this->collider.width = 0;
	this->collider.height = 0;
	this->collider.dt = 0;
}

Sword::~Sword()
{
}
