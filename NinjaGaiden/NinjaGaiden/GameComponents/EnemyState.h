#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"

class EnemyState :
	public State
{
private:
	Enemy* enemy;
	int enemystate;
public:
	EnemyState(){};
	EnemyState(Enemy* enemy, int enemystates);
	~EnemyState();

	void Jump() override;
	void Crouch() override;
	void JumpAttack() override;
	void Climb() override;

	void Idle() override;
	void Attack() override;
	void Walk() override;

	virtual void Update(DWORD dt);
	virtual void Render();
};

