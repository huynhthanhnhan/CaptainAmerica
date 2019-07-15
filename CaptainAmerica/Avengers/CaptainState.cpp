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
	int state = this->states;
	switch (state)
	{
	case CAPTAIN_ANI_JUMPING:
	{
		if (captain->IsGrounded())
		{
			captain->SetState(captain->GetIdleState());
		}
		if (captain->GetPositionY() >= TiledMap::GetInstance()->GetHeight() + 20)
		{
			captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_GRAVITY);
		}
	}
	break;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

#pragma region	Collide with brick
	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();
	//if (state != NINJA_ANI_CLIMBING)
	{
		captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_GRAVITY);
	}
	coEvents.clear();
	captain->SetDt(dt);
	captain->CalcPotentialCollisions(tiles, coEvents);

	if (coEvents.size() == 0)
	{
		float moveX = trunc(captain->GetSpeedX()* dt);
		float moveY = trunc(captain->GetSpeedY()* dt);
		captain->SetPositionX(captain->GetPositionX() + moveX);
		captain->SetPositionY(captain->GetPositionY() + moveY);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		captain->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * captain->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * captain->GetSpeedY() * dt + ny * 0.4;

		captain->SetPositionX(captain->GetPositionX() + moveX);
		captain->SetPositionY(captain->GetPositionY() + moveY);


		if (nx != 0) captain->SetSpeedX(0);
		if (ny != 0) captain->SetSpeedY(0);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				captain->SetIsGrounded(true);
			}
		}
	}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	#pragma endregion

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
