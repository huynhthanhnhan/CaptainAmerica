#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "Boss.h"

class BossState :
	public EnemyState
{
private:
	Boss* enemy;
	int enemystate;
public:
	BossState(Boss* enemy, int enemystates);
	~BossState();

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

