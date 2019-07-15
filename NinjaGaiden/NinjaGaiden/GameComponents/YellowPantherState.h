#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "YellowPanther.h"

class YellowPantherState :
	public EnemyState
{
private:
	YellowPanther* enemy;
	int enemystate;
public:
	YellowPantherState(YellowPanther* enemy, int enemystates);
	~YellowPantherState();

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

