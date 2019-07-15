#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "BloodyBird.h"

class BloodyBirdState :
	public EnemyState
{
private:
	BloodyBird* enemy;
	int enemystate;
public:
	BloodyBirdState(BloodyBird* enemy, int enemystates);
	~BloodyBirdState();

	void Jump() override;
	void Crouch() override;
	void JumpAttack() override;
	void Climb() override;

	void Idle() override;
	void Attack() override;
	void Walk() override;

	void Update(DWORD dt) override;
	void Render() override;
};

