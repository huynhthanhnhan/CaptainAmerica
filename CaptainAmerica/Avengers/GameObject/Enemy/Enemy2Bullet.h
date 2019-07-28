#pragma once
#include "../../GameFramework/GameObject.h"

class Enemy2Bullet : public GameObject
{
	float timeLife = 100;

	float countTimeLife = 0;

	float maxDistance;

	bool isDestroyed = false;

	bool isRightToLeft;

	vector<Animation *> animation;

public:
	Enemy2Bullet(float posX, float posY, bool isRightToLeft);

	vector<Animation*> GetAnimationList() { return this->animation; }

	void LoadResource();

	bool GetIsDestroyed() { return this->isDestroyed; }
	void SetIsDestroyed(bool b) { this->isDestroyed = b; }

	void Update(DWORD dt);
	void Render();

	~Enemy2Bullet();
};

