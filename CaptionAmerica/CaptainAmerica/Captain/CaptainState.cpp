#include "CaptainState.h"
#include <math.h>

CaptainState::CaptainState(Captain * captain, int states)
{
	this->captain = captain;
	this->states = states;
}

CaptainState::~CaptainState()
{
}

void CaptainState::Idle()
{
	int state = this->states;
	captain->SetColliderDemension(24, 45);
	switch (state)
	{
	case CAPTAIN_ANI_IDLE:
		break;
	case CAPTAIN_ANI_CROUCHING:
	{
		captain->SetIsCrouching(false);
		captain->SetState(captain->GetIdleState());
	}
	break;
	case CAPTAIN_ANI_WALKING:
	{
		captain->SetSpeedX(0);
		captain->SetState(captain->GetIdleState());
	}
	break;
	}
}

void CaptainState::Walk()
{
	int state = this->states;
	captain->SetColliderDemension(22, 45);
	switch (state)
	{
	case CAPTAIN_ANI_CROUCHING:
	case CAPTAIN_ANI_JUMPING:
		break;
	case CAPTAIN_ANI_IDLE:
	{
		captain->SetSpeedX(CAPTAIN_WALKING_SPEED * (captain->IsLeft() ? -1 : 1));
		captain->SetState(captain->GetWalkingState());
	}
	break;
	case CAPTAIN_ANI_WALKING:
	{
		captain->SetSpeedX(CAPTAIN_WALKING_SPEED * (captain->IsLeft() ? -1 : 1));
	}
	break;
	}
}

void CaptainState::Jump()
{
	int state = this->states;

	switch (state)
	{
	case CAPTAIN_ANI_CROUCHING:
	case CAPTAIN_ANI_JUMPING:
		break;
	case CAPTAIN_ANI_IDLE:
	case CAPTAIN_ANI_WALKING:
	{
		if (captain->IsGrounded())
		{
			captain->SetIsGrounded(false);
			captain->SetSpeedY(CAPTAIN_JUMP_SPEED_Y);
			captain->SetState(captain->GetJumpingState());
		}
	}
	break;
	}
}

void CaptainState::Crouch()
{
	{
		int state = this->states;

		switch (state)
		{
		case CAPTAIN_ANI_CROUCHING:
		case CAPTAIN_ANI_JUMPING:
			break;
		case CAPTAIN_ANI_IDLE:
		{
			captain->SetIsCrouching(true);
			captain->SetState(captain->GetCrouchingState());
		}
		break;
		case CAPTAIN_ANI_WALKING:
		{
			captain->SetSpeedX(0);
			captain->SetIsCrouching(true);
			captain->SetState(captain->GetCrouchingState());
		}
		break;
		}
	}
}
void CaptainState::Update(DWORD dt)
{

}

void CaptainState::Render()
{
	int state = this->states;

	SpriteData spriteData;
	if (this->captain != NULL)
	{
		spriteData.width = 25;
		spriteData.height = 45;
		spriteData.x = captain->GetPositionX();
		spriteData.y = captain->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = captain->IsLeft();
		spriteData.isFlipped = captain->IsFlipped();
	}

	switch (state)
	{
	case CAPTAIN_ANI_IDLE:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_IDLE]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_CROUCHING:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_CROUCHING]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_JUMPING:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_JUMPING]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_WALKING:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_WALKING]->Render(spriteData);
	}
	break;
	}
}
