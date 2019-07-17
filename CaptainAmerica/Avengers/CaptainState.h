#pragma once
#include "State.h"
#include "GameComponents/Constants.h"
#include "Captain.h"

class CaptainState : public State
{
private:
	Captain * captain;
	int states;
public:
	CaptainState(Captain * ninja, int states);
	~CaptainState();

	int GetState();

	void Idle() override;
	void Walk() override;
	void Jump() override;
	void Crouch() override;

	void Update(DWORD dt) override;
	void Render() override;
};

