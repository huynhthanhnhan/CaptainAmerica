#pragma once
#include "../../GameFramework/GameObject.h"

class Enemy1Bullet : public GameObject
{
	float timeLife = 100;

	float countTimeLife = 0;

	float maxDistance;

	bool isRightToLeft;

	vector<Animation *> animation;

public:
	Enemy1Bullet(float posX, float posY, bool isRightToLeft);

	vector<Animation*> GetAnimationList() { return this->animation; }

	void LoadResource();

	void Update(DWORD dt);
	void Render();

	~Enemy1Bullet();
};

