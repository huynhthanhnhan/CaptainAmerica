#pragma once
#include "../../GameFramework/State.h"
#include "../../GameFramework/Global.h"
#include "Captain.h"
#include "Shield.h"

class CaptainState : public State
{
private:
	Captain * captain;
	int state;
public:
	CaptainState(Captain * captain, eCaptainState state);
	~CaptainState();

	int GetState();

	void SetNewState(eCaptainState state, eController control);

	void Jump() override;
	void Idle() override;
	void Walk() override;
	void Crouch() override;
	void ThrowShield() override;
	void Roll() override;
	void Kick() override;
	void StandHit() override;
	void CrouchHit() override;
	void SitOnShield() override;
	void Swing() override;
	void Wade() override;
	void ShieldUp() override;
	void GetHurt() override;
	void Dead() override;
	void Dash() override;

	void Update(DWORD dt) override;
	void Render() override;
};

