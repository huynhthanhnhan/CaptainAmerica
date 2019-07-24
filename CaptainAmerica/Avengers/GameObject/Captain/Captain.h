#pragma once
#include "../GameComponents/GameObject.h"
#include "../../GameFramework/State.h"
#include "../../GameFramework/Global.h"
#include "../../GameObject/GameComponents/Game.h"
#include "CaptainState.h"
#include "Shield.h"

namespace NS
{
	const int idle_start = 0;
	const int walk_start = 1;
	const int walk_end = 4;
	const int jump_start = 7;
	const int jump_end = 9;
	const int crouch_start = 6;
	const int throw_shiled_start = 11;
	const int throw_shield_end = 12;
	const int roll_start = 8;
	const int roll_end = 9;
	const int kick_start = 10;
	const int stand_hit_start = 13;
	const int stand_hit_end = 14;
	const int crouch_hit_start = 15;
	const int crouch_hit_end = 16;
	const int sit_on_shiled_start = 19;
	const int swing_start = 17 ;
	const int swing_end = 29;
	const int wade_start = 44;
	const int wade_end = 45;
	const int shield_up_start = 5;
	const int hurt_start = 33;
	const int dead_start = 34;
	const int dead_end = 35;
	const int dash_start = 17;
	const int dash_end = 18;
}

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
	State *dashState;

	State * state;
	eCaptainState eState;

	Shield* shield;

	int StateNum;

	bool isGrounded = false;
	bool isCrouching = false;
	bool isShieldUp = false;
	bool isDash = false;
	
	

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	int score = 0;
	int captain_item = 0;
	int support_item = 0;
	int stamina;
public:

	static Captain * GetInstance();

	void LoadResources();

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }

	void SetIsCrouching(bool isCrouching) { this->isCrouching = isCrouching; }

	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetState(State * state);

	int GetStateNum() { return this->StateNum; }
	void SetStateNum(int num) { this->StateNum = num; }

	State * GetState() { return this->state; }

	eCaptainState GetEnumState() { return this->eState; }
	void SetEnumState(eCaptainState state) { this->eState = state; }
	
	bool isThrowing = false;
	bool isFalling = false;
	bool isWading = false;

	void SetIsShieldUp(bool isShieldUp) { this->isShieldUp = isShieldUp; }

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
	State *GetDashState();

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
	void Dash();

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

