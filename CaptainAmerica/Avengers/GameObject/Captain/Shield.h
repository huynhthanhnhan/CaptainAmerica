#pragma once
#include "../../GameFramework/GameItem.h"
#include "../../GameFramework/State.h"

class Shield : public GameItem
{
	int damage = 10;

	vector<Animation *> animations;
	static Shield * __instance;

	int state;

	bool Active;

	bool isStart = true;

	bool isReturn = true;

	bool isCaptainLeft;

	float maxDistance;

	float distance;
public:
	Shield();

	int GetDamage() { return this->damage; }

	bool GetIsStart() { return this->isStart; }

	void SetState(int state) { this->state = state; }

	void SheildAttacking();

	static Shield * GetInstance();

	void LoadResources();

	void Update(DWORD dt) override;
	void Render() override;

	float GetDistance() { return this->distance; }

	~Shield();
};

