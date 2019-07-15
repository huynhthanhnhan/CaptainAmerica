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
	virtual void Attack();

	virtual void Update(DWORD dt);
	virtual void Render();
};

