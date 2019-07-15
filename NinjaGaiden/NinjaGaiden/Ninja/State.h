#pragma once
#include "d3d9.h"

class Ninja;
class Enemy;
class State
{
protected:
	
public:
	State();
	virtual void Jump();
	virtual void Crouch();
	virtual void JumpAttack();
	virtual void Climb();
	virtual void Idle();
	virtual void Attack();
	virtual void Walk();

	virtual void Attacked();

	virtual void Update(DWORD dt);
	virtual void Render();
};

