#pragma once
#include "GameComponents/GameObject.h"
#include "State.h"
#include "GameComponents/Constants.h"
#include "GameComponents/Game.h"
#include "CaptainState.h"
#include "Shield.h"

class Captain : public GameObject
{
	Captain();
	static Captain * __instance;

	State *idleState;
	State *walkState;
	State *jumpState;
	State *crouchState;
	State *throwShieldState;
	State *rollState;
	State *kickState;
	State *standHitState;
	State *crouchHitState;
	State *sitOnShieldState;
	State *swingState;
	State *wadeState;
	State *shieldUpState;
	State *getHurtState;
	State *deadState;

	State * state;

	Shield* shield;

	int StateNum;

	bool isGrounded = false;
	bool isCrouching = false;
	

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	int score = 0;
	int captain_item = 0;
	int support_item = 0;
	int stamina;
public:
	void LoadResources();

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	void SetIsCrouching(bool isCrouching) { this->isCrouching = isCrouching; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }
	void SetState(State * state);
	int GetStateNum() { return this->StateNum; }
	void SetStateNum(int num) { this->StateNum = num; }
	State * GetState() { return this->state; }
	static Captain * GetInstance();
	bool isThrowing = false;

	DWORD GetLastFrameTime() { return this->lastFrameTime; }

	State *GetIdleState();
	State *GetWalkState();
	State *GetJumpState();
	State *GetCrouchState();
	State *GetThrowShieldState();
	State *GetRollState();
	State *GetKickState();
	State *GetStandHitState();
	State *GetCrouchHitState();
	State *GetSitOnShieldState();
	State *GetSwingState();
	State *GetWadeState();
	State *GetShieldUpState();
	State *GetGetHurtState();
	State *GetDeadState();

	bool IsGrounded() { return isGrounded; }
	bool IsCrouching() { return isCrouching; }
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? false : true; return isFlipped; }

	void Idle();
	void Walk();
	void Jump();
	void Crouch();
	void ThrowShield();
	void Roll();
	void Kick();
	void StandHit();
	void CrouchHit();
	void SitOnShield();
	void Swing();
	void Wade();
	void ShieldUp();
	void GetHurt();
	void Dead();

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}
	void SetScore(int value) { this->score = value; }
	int GetScore() { return this->score; }


	int GetStamina() { return this->stamina; }
	int GetSupportItem() { return this->support_item; }
	void TakeDamage(int value) { this->stamina -= value; }
	void Reset();
	void TurnLeft();
	void TurnRight();

	vector<Animation *> GetAnimationsList() { return animations; }

	void Update(DWORD dt) override;

	void Render() override;
};

