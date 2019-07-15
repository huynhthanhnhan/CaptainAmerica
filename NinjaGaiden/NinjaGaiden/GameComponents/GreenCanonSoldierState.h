#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "GreenCanonSoldier.h"

class GreenCanonSoldierState :
	public EnemyState
{
private:
	GreenCanonSoldier* enemy;
	int enemystate;
public:
	GreenCanonSoldierState(GreenCanonSoldier* enemy, int enemystates);
	~GreenCanonSoldierState();

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

