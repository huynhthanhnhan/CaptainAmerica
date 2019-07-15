#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "YellowSolider.h"

class YellowSoliderState :
	public EnemyState
{
private:
	YellowSolider* enemy;
	int enemystate;
public:
	YellowSoliderState(YellowSolider* enemy, int enemystates);
	~YellowSoliderState();

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

