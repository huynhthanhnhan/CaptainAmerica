#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "BrownBird.h"

class BrownBirdState :
	public EnemyState
{
private:
	BrownBird* enemy;
	int enemystate;
public:
	BrownBirdState(BrownBird* enemy, int enemystates);
	~BrownBirdState();

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

