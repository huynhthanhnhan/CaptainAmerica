#pragma once
#include "../../GameFramework/State.h"
#include "../../GameFramework/Global.h"
#include "Captain.h"
#include "Shield.h"

class CaptainState : public State
{
private:
	Captain * captain;
	eCaptainState state;
public:
	CaptainState(Captain * captain, eCaptainState state);
	~CaptainState();

	int GetState();

	void SetNewState(eCaptainState state, eController control);

	void Update(DWORD dt) override;
	void Render() override;
};
