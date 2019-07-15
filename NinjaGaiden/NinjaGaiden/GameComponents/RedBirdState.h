#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "RedBird.h"

class RedBirdState :
	public EnemyState
{
private:
	RedBird* enemy;
	int enemystate;
public:
	RedBirdState(RedBird* enemy, int enemystates);
	~RedBirdState();

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

