#pragma once
#include "State.h"
#include "Constants.h"
#include "Enemy.h"
#include "PinkWitch.h"

class PinkWitchState :
	public EnemyState
{
private:
	PinkWitch* enemy;
	int enemystate;
public:
	PinkWitchState(PinkWitch* enemy, int enemystates);
	~PinkWitchState();

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


