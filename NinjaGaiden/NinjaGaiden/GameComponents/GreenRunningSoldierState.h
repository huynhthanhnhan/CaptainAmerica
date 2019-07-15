#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "GreenRunningSoldier.h"

class GreenRunningSoldierState :
	public EnemyState
{
private:
	GreenRunningSoldier* enemy;
	int enemystate;
public:
	GreenRunningSoldierState(GreenRunningSoldier* enemy, int enemystates);
	~GreenRunningSoldierState();

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

