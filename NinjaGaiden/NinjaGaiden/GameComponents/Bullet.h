#pragma once
#include "GameObject.h"

class Bullet :
	public GameObject
{
protected:
	vector<Animation *> animations;
	Enemy* enemy;

	bool Active;
	float distance;
	int damage;

	int shootTime;

	BulletType bullettype = BulletType::NORMAL;
public:
	Bullet();
	int GetDamage() { return this->damage; }

	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
	Enemy* GetEnemy() { return this->enemy; }
	virtual void Update(DWORD dt);
	virtual void Render();

	float GetDistance() { return this->distance; }

	BulletType GetBulletType() { return this->bullettype; }
	void SetBulletType(BulletType type) { this->bullettype = type; }

	int GetShootTime() { return this->shootTime; }
	void ResetShootTime() { this->shootTime = 0; }

	virtual void Reset();
	~Bullet();
};

