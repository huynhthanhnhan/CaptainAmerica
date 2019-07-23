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

int CaptainState::GetState() 
{
	return this->states;
}

void CaptainState::Idle()
{
	int state = this->states;
	captain->SetColliderDemension(24, 45);
	switch (state)
	{
	case CAPTAIN_ANI_IDLE:
		captain->SetSpeedX(0);
		break;
	case CAPTAIN_ANI_CROUCH:
	{
		captain->SetIsCrouching(false);
		captain->SetState(captain->GetIdleState());
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->SetSpeedX(0);
		captain->SetState(captain->GetIdleState());
	}
	break;
	case CAPTAIN_ANI_DASH:
	{
		captain->SetSpeedX(0);
		captain->SetState(captain->GetIdleState());
	}
	case CAPTAIN_ANI_THROW_SHIELD:
	case CAPTAIN_ANI_SHIELD_UP:
		captain->SetState(captain->GetIdleState());
		break;
	}
}

void CaptainState::Walk()
{
	int state = this->states;
	captain->SetColliderDemension(22, 45);
	switch (state)
	{
	case CAPTAIN_ANI_CROUCH:
	case CAPTAIN_ANI_JUMP:
		break;
	case CAPTAIN_ANI_IDLE:
	case CAPTAIN_ANI_DASH:
	{
		captain->SetSpeedX(CAPTAIN_WALKING_SPEED * (captain->IsLeft() ? -1 : 1));
		captain->SetState(captain->GetWalkState());
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->SetSpeedX(CAPTAIN_WALKING_SPEED * (captain->IsLeft() ? -1 : 1));
	}
	break;
	case CAPTAIN_ANI_THROW_SHIELD:
		captain->SetState(captain->GetIdleState());
		break;
	}
}

void CaptainState::Jump()
{
	int state = this->states;

	switch (state)
	{
	case CAPTAIN_ANI_CROUCH:
	case CAPTAIN_ANI_CROUCH_HIT:
		captain->SetSpeedY(0);
		break;
	case CAPTAIN_ANI_JUMP:
	case CAPTAIN_ANI_KICK:
		if (captain->GetSpeedY() > 0.4) 
		{
			captain->isFalling = true;
		}
		break;
	case CAPTAIN_ANI_IDLE:
	case CAPTAIN_ANI_WALK:
	{
		if (captain->IsGrounded())
		{
			captain->SetIsGrounded(false);
			captain->SetSpeedY(CAPTAIN_JUMP_SPEED_Y);
			captain->SetState(captain->GetJumpState());
		}
	}
	break;
	case CAPTAIN_ANI_WADE:
	{
		if (captain->isWading)
		{
			captain->isWading = false;
			captain->SetSpeedY(CAPTAIN_JUMP_SPEED_Y);
			captain->SetState(captain->GetJumpState());
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
		case CAPTAIN_ANI_CROUCH:
		case CAPTAIN_ANI_JUMP:
			break;
		case CAPTAIN_ANI_IDLE:
		{
			captain->SetIsCrouching(true);
			captain->SetState(captain->GetCrouchState());
		}
		break;
		case CAPTAIN_ANI_WALK:
		case CAPTAIN_ANI_CROUCH_HIT:
		{
			captain->SetSpeedX(0);
			captain->SetIsCrouching(true);
			captain->SetState(captain->GetCrouchState());
		}
		break;
		}
	}
}

void CaptainState::ThrowShield()
{

	int state = this->states;
	switch (state)
	{
	case CAPTAIN_ANI_CROUCH:
	case CAPTAIN_ANI_CROUCH_HIT:
		break;
	case CAPTAIN_ANI_IDLE:
	case CAPTAIN_ANI_WALK:
	{
		captain->isThrowing = true;
		captain->SetState(captain->GetThrowShieldState());
	}
	break;
	case CAPTAIN_ANI_JUMP:
		captain->SetState(captain->GetJumpState());
		break;
	}
}

void CaptainState::Roll()
{
	int state = this->states;
}

void CaptainState::Kick()
{
	int state = this->states;
	switch (state)
	{
	case CAPTAIN_ANI_JUMP:
	{
		captain->SetIsGrounded(false);
		captain->SetState(captain->GetKickState());
		break;
	}
	case CAPTAIN_ANI_KICK:
		if (captain->GetSpeedY() > 0.4)
		{
			captain->isFalling = true;
		}
		break;
	}
}

void CaptainState::StandHit()
{
	int state = this->states;
}

void CaptainState::CrouchHit()
{
	int state = this->states;
	captain->SetState(captain->GetCrouchHitState());
}

void CaptainState::SitOnShield()
{
	int state = this->states;
}

void CaptainState::Swing()
{
	int state = this->states;
}

void CaptainState::Wade()
{
	int state = this->states;
	captain->SetSpeedX(0);
	captain->SetState(captain->GetWadeState());
}

void CaptainState::ShieldUp()
{
	int state = this->states;

	switch (state)
	{
	case CAPTAIN_ANI_SHIELD_UP:
	case CAPTAIN_ANI_JUMP:
		break;
	case CAPTAIN_ANI_IDLE:
	{
		captain->SetIsShieldUp(true);
		captain->SetState(captain->GetShieldUpState());
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->SetSpeedX(0);
		captain->SetIsShieldUp(true);
		captain->SetState(captain->GetShieldUpState());
	}
	break;
	}
}

void CaptainState::GetHurt()
{
	int state = this->states;
}

void CaptainState::Dead()
{
	int state = this->states;
}
void CaptainState::Dash()
{
	int state = this->states;
	switch (state)
	{
		case CAPTAIN_ANI_WALK:
		case CAPTAIN_ANI_IDLE:
			captain->SetSpeedX(CAPTAIN_WALKING_SPEED * 2 * (captain->IsLeft() ? -1 : 1));
			captain->SetState(captain->GetDashState());
			break;

	}
}

void CaptainState::Update(DWORD dt)
{
	int state = this->states;
	switch (state)
	{
	case CAPTAIN_ANI_KICK:
	case CAPTAIN_ANI_JUMP:
	{
		if (captain->IsGrounded())
		{
			captain->isFalling = false;
			captain->SetState(captain->GetIdleState());
		}
		if (captain->GetPositionY() >= TiledMap::GetInstance()->GetHeight() + 20)
		{
			captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_GRAVITY);
		}
	}
	break;
	}
	if (captain->isWading)
		captain->SetState(captain->GetWadeState());

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
		if (coEventsResult[0]->collisionID == 2)
		{
			if (ny == 1)
			{
				captain->SetIsGrounded(false);
				captain->isWading = true;
				captain->Wade();
				captain->SetPositionX(captain->GetPositionX() + 0.75);
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
	case CAPTAIN_ANI_CROUCH:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_CROUCH]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_JUMP:
	{
		if (captain->GetSpeedY() >= 0.25)
		{
			Shield::GetInstance()->SetState(NO_SHIELD);
			if (captain->GetAnimationsList()[CAPTAIN_ANI_JUMP]->GetCurFrame() == 4)
				captain->GetAnimationsList()[CAPTAIN_ANI_JUMP]->SetCurFrame(0);
		}
		else
		{
			Shield::GetInstance()->SetState(SHIELD_CENTER);
			if (captain->GetAnimationsList()[CAPTAIN_ANI_JUMP]->GetCurFrame() == 1)
				captain->GetAnimationsList()[CAPTAIN_ANI_JUMP]->SetCurFrame(0);
		}
		captain->GetAnimationsList()[CAPTAIN_ANI_JUMP]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_WALK]->Render(spriteData);
	}
	break;

	case CAPTAIN_ANI_THROW_SHIELD:
	{
		/*if (captain->GetAnimationsList()[CAPTAIN_ANI_THROW_SHIELD]->GetCurFrame() == 1)
			captain->GetAnimationsList()[CAPTAIN_ANI_THROW_SHIELD]->SetCurFrame(0);*/
		captain->GetAnimationsList()[CAPTAIN_ANI_THROW_SHIELD]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_ROLL:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_ROLL]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_KICK:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_KICK]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_STAND_HIT:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_STAND_HIT]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_CROUCH_HIT:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_CROUCH_HIT]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_SIT_ON_SHIELD:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_SIT_ON_SHIELD]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_SWING:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_SWING]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_WADE:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_WADE]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_SHIELD_UP:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_SHIELD_UP]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_GET_HURT:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_GET_HURT]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_DEAD:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_DEAD]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_DASH:
	{
		if (captain->GetAnimationsList()[CAPTAIN_ANI_DASH]->GetCurFrame() == 0)
			captain->GetAnimationsList()[CAPTAIN_ANI_DASH]->SetCurFrame(1);
		captain->GetAnimationsList()[CAPTAIN_ANI_DASH]->Render(spriteData);
	}
	break;
	}
}
