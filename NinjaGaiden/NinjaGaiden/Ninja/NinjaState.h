#pragma once
#include "NinjaState.h"
#include "Constants.h"
#include "Ninja.h"

class NinjaState : public State
{
private:
	Ninja * ninja;
	int states;
public:
	NinjaState(Ninja * ninja, int states);
	~NinjaState();

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

