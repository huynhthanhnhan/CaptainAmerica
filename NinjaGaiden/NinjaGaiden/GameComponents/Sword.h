#pragma once
#include "GameObject.h"

class Sword : public GameObject
{
private :

	Sword();
	static Sword * __instance;

	int damage;

	int attacktime;
public:
	static Sword * GetInstance();
	void SetPosition(float posx, float posy , float dt)
	{
		this->x = posx;
		this->y = posy;
		collider.x = posx;
		collider.y = posy;
		this->dt = dt;
	}
	int GetDamage() { return this->damage; }
	int GetAttackTime() { return this->attacktime; }
	void SetAttackTime(int value) { this->attacktime -= value; }


	void ResetAttackTime();
	void ResetCollider();
	~Sword();
};

