#pragma once
#include "GameObject.h"
#include "State.h"
#include "Constants.h"
#include "Game.h"
#include "NinjaSate.h"
#include "Shuriken.h"

class Ninja : public GameObject
{
	Ninja();
	static Ninja * __instance;

	State * idleState;
	State * walkingState;
	State * crouchingState;
	State * jumpingState;
	State * attackingState;
	State * jumpattackingState;
	State * jumpattackedState;
	State * throwingState;
	State * climbState;

	State * state;

	bool isGrounded = false;
	bool isCrouching = false;
	bool isClimbing = false;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	int score = 0;
	int ninja_item = 0;
	int support_item = 0;
	int stamina;

	bool isUntouchable;
	int UntouchableTime;

	vector<Shuriken *> Shurikens;

	bool isThrowing;
	bool checkItem;

	bool isAttacked = false;
public:
	void LoadResources();

	void SetCheckItem(bool x) { this->checkItem = x; }
	bool GetCheckItem() { return this->checkItem; }

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	void SetIsCrouching(bool isCrouching) { this->isCrouching = isCrouching; }
	void SetIsClimbing(bool isClimbing) { this->isClimbing = isClimbing; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }
	void SetState(State * state);
	State * GetSate() { return this->state; }
	static Ninja * GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }

	State * GetIdleState();
	State * GetWalkingState();
	State * GetAttackingState();
	State * GetAttackedState();
	State * GetThrowingState();
	State * GetCrouchingState();
	State * GetJumpingState();
	State * GetClimbState();
	State * GetJumpAttackState();

	bool IsAttacking() { return state == attackingState || state == throwingState; }
	bool IsGrounded() { return isGrounded; }
	bool IsCrouching() { return isCrouching; }
	bool IsClimbing() { return isClimbing; }
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? false : true; return isFlipped; }
	bool IsThrowing() { return this->isThrowing; }
	void SetClimming(bool value) { this->isClimbing = value; }
	bool IsAttacked() { return this->isAttacked; }
	void SetAttacked(bool value) { this->isAttacked = value; }

	void Idle();
	void Attack();
	void Walk();
	void Jump();
	void Crouch();
	void Climb();
	void JumpAttack();
	void Attacked();

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}
	void SetScore(int value) { this->score = value; }
	int GetScore() { return this->score; }

	bool IsUntouchable() { return this->isUntouchable; }
	void SetUntouchable(bool value) { this->isUntouchable = value; }
	void SetUntouchableTime(int dt);
	int GetUntouchableTime() { return this->UntouchableTime; }

	void DescreaseShuriken();
	int GetStamina() { return this->stamina; }
	int GetItem() { return this->ninja_item; }
	int GetSupportItem() { return this->support_item; }
	void TakeDamage(int value) { this->stamina -= value; }
	void SetThrowing(bool value) { this->isThrowing = value; }
	void Reset();
	void CreateThrownWeapon();
	void TurnLeft();
	void TurnRight();

	vector<Animation *> GetAnimationsList() { return animations; }
	vector<Shuriken *> GetShuriken() { return this->Shurikens; }

	void Additem(GameItem * gameitem);

	void Update(DWORD dt) override;

	void Render() override;
};

