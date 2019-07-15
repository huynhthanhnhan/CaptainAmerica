#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "GreenSolider.h"

class GreenSoliderState :
	public EnemyState
{
private:
	GreenSolider* enemy;
	int enemystate;
public:
	GreenSoliderState(GreenSolider* enemy, int enemystates);
	~GreenSoliderState();

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


