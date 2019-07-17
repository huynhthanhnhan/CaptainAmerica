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

	State * idleState;
	State * walkingState;
	State * crouchingState;
	State * jumpingState;

	State * state;

	Shield* shield;

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
	State * GetState() { return this->state; }
	static Captain * GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }

	State * GetIdleState();
	State * GetWalkingState();
	State * GetJumpingState();
	State * GetCrouchingState();

	bool IsGrounded() { return isGrounded; }
	bool IsCrouching() { return isCrouching; }
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? false : true; return isFlipped; }

	void Idle();
	void Walk();
	void Jump();
	void Crouch();

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

