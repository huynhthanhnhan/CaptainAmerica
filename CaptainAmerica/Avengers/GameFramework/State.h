#pragma once
#include "d3d9.h"

class Captain;
class Enemy;
class State
{
protected:

public:
	State();
	virtual void Idle();
	virtual void Walk();
	virtual void Jump();
	virtual void Crouch();
	virtual void ThrowShield();
	virtual void Roll();
	virtual void Kick();
	virtual void StandHit();
	virtual void CrouchHit();
	virtual void SitOnShield();
	virtual void Swing();
	virtual void Wade();
	virtual void ShieldUp();
	virtual void GetHurt();
	virtual void Dead();
	virtual void Dash();

	virtual void Update(DWORD dt);
	virtual void Render();
};

