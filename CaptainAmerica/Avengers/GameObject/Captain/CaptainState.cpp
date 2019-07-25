#include "CaptainState.h"
#include <math.h>

CaptainState::CaptainState(Captain * captain, eCaptainState state)
{
	this->captain = captain;
	this->state = state;
}

CaptainState::~CaptainState()
{
}

int CaptainState::GetState() 
{
	return this->state;
}

void CaptainState::Idle()
{
	int state = this->state;
	captain->SetColliderDemension(24, 45);
	switch (state)
	{
	case eCaptainState::IDLE:
		captain->SetSpeedX(0);
		break;
	case eCaptainState::CROUCH:
	{
		captain->SetIsCrouching(false);
		captain->SetState(captain->GetIdleState());
	}
	break;
	case eCaptainState::WALK:
	{
		captain->SetSpeedX(0);
		captain->SetState(captain->GetIdleState());
	}
	break;
	case eCaptainState::DASH:
	{
		captain->SetSpeedX(0);
		captain->SetState(captain->GetIdleState());
	}
	case eCaptainState::THROW_SHIELD:
	case eCaptainState::SHIELD_TOP:
		captain->SetState(captain->GetIdleState());
		break;
	}
}

void CaptainState::Walk()
{
	int state = this->state;
	captain->SetColliderDemension(22, 45);
	switch (state)
	{
	case eCaptainState::CROUCH:
	case eCaptainState::JUMP:
		break;
	case eCaptainState::IDLE:
	case eCaptainState::DASH:
	{
		captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
		captain->SetState(captain->GetWalkState());
	}
	break;
	case eCaptainState::WALK:
	{
		captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
	}
	break;
	case eCaptainState::THROW_SHIELD:
		captain->SetState(captain->GetIdleState());
		break;
	}
}

void CaptainState::Jump()
{
	int state = this->state;

	switch (state)
	{
	case eCaptainState::CROUCH:
	case eCaptainState::CROUCH_HIT:
		captain->SetSpeedY(0);
		break;
	case eCaptainState::JUMP:
	case eCaptainState::KICK:
		if (captain->GetSpeedY() > 0.4) 
		{
			captain->isFalling = true;
		}
		break;
	case eCaptainState::IDLE:
	case eCaptainState::WALK:
	{
		if (captain->IsGrounded())
		{
			captain->SetIsGrounded(false);
			captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
			captain->SetState(captain->GetJumpState());
		}
	}
	break;
	case eCaptainState::WADE:
	{
		if (captain->isWading)
		{
			captain->isWading = false;
			captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
			captain->SetState(captain->GetJumpState());
		}
	}
	break;
	}
}


void CaptainState::Crouch()
{
	{
		int state = this->state;

		switch (state)
		{
		case eCaptainState::CROUCH:
		case eCaptainState::JUMP:
			break;
		case eCaptainState::IDLE:
		{
			captain->SetIsCrouching(true);
			captain->SetState(captain->GetCrouchState());
		}
		break;
		case eCaptainState::WALK:
		case eCaptainState::CROUCH_HIT:
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

	int state = this->state;
	switch (state)
	{
	case eCaptainState::CROUCH:
	case eCaptainState::CROUCH_HIT:
		break;
	case eCaptainState::IDLE:
	case eCaptainState::WALK:
	{
		captain->isThrowing = true;
		captain->SetState(captain->GetThrowShieldState());
	}
	break;
	case eCaptainState::JUMP:
		captain->SetState(captain->GetJumpState());
		break;
	}
}

void CaptainState::Roll()
{
	int state = this->state;
}

void CaptainState::Kick()
{
	int state = this->state;
	switch (state)
	{
	case eCaptainState::JUMP:
	{
		captain->SetIsGrounded(false);
		captain->SetState(captain->GetKickState());
		break;
	}
	case eCaptainState::KICK:
		if (captain->GetSpeedY() > 0.4)
		{
			captain->isFalling = true;
		}
		break;
	}
}

void CaptainState::StandHit()
{
	int state = this->state;
}

void CaptainState::CrouchHit()
{
	int state = this->state;
	captain->SetState(captain->GetCrouchHitState());
}

void CaptainState::SitOnShield()
{
	int state = this->state;
}

void CaptainState::Swing()
{
	int state = this->state;
}

void CaptainState::Wade()
{
	int state = this->state;
	captain->SetSpeedX(0);
	captain->SetState(captain->GetWadeState());
}

void CaptainState::ShieldUp()
{
	int state = this->state;

	switch (state)
	{
	case eCaptainState::SHIELD_TOP:
	case eCaptainState::JUMP:
		break;
	case eCaptainState::IDLE:
	{
		captain->SetIsShieldUp(true);
		captain->SetState(captain->GetShieldUpState());
	}
	break;
	case eCaptainState::WALK:
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
	int state = this->state;
}

void CaptainState::Dead()
{
	int state = this->state;
}
void CaptainState::Dash()
{
	int state = this->state;
	switch (state)
	{
		case eCaptainState::WALK:
		case eCaptainState::IDLE:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * 2 * (captain->IsLeft() ? -1 : 1));
			captain->SetState(captain->GetDashState());
			break;

	}
}

void CaptainState::Update(DWORD dt)
{
	int state = this->state;
	switch (state)
	{
	case eCaptainState::KICK:
	case eCaptainState::JUMP:
	{
		if (captain->IsGrounded())
		{
			captain->isFalling = false;
			captain->SetState(captain->GetIdleState());
		}
		if (captain->GetPositionY() >= CMap::GetInstance()->GetHeight() + 20)
		{
			captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_AMERICA_GRAVITY);
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
	//if (state != NINJA_ANIMATION_CLIMBING)
	{
		captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_AMERICA_GRAVITY);
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
	int state = this->state;

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
	case eCaptainState::IDLE:
	{
		captain->GetAnimationsList()[eCaptainState::IDLE]->Render(spriteData);
	}
	break;
	case eCaptainState::CROUCH:
	{
		captain->GetAnimationsList()[eCaptainState::CROUCH]->Render(spriteData);
	}
	break;
	case eCaptainState::JUMP:
	{
		if (captain->GetSpeedY() >= 0.25)
		{
			Shield::GetInstance()->SetState(NO_SHIELD);
			if (captain->GetAnimationsList()[eCaptainState::JUMP]->GetCurFrame() == 4)
				captain->GetAnimationsList()[eCaptainState::JUMP]->SetCurFrame(0);
		}
		else
		{
			Shield::GetInstance()->SetState(SHIELD_CENTER);
			if (captain->GetAnimationsList()[eCaptainState::JUMP]->GetCurFrame() == 1)
				captain->GetAnimationsList()[eCaptainState::JUMP]->SetCurFrame(0);
		}
		captain->GetAnimationsList()[eCaptainState::JUMP]->Render(spriteData);
	}
	break;
	case eCaptainState::WALK:
	{
		captain->GetAnimationsList()[eCaptainState::WALK]->Render(spriteData);
	}
	break;

	case eCaptainState::THROW_SHIELD:
	{
		/*if (captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->GetCurFrame() == 1)
			captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->SetCurFrame(0);*/
		captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->Render(spriteData);
	}
	break;
	case eCaptainState::ROLL:
	{
		captain->GetAnimationsList()[eCaptainState::ROLL]->Render(spriteData);
	}
	break;
	case eCaptainState::KICK:
	{
		captain->GetAnimationsList()[eCaptainState::KICK]->Render(spriteData);
	}
	break;
	case eCaptainState::STAND_HIT:
	{
		captain->GetAnimationsList()[eCaptainState::STAND_HIT]->Render(spriteData);
	}
	break;
	case eCaptainState::CROUCH_HIT:
	{
		captain->GetAnimationsList()[eCaptainState::CROUCH_HIT]->Render(spriteData);
	}
	break;
	case eCaptainState::SIT_ON_SHIELD:
	{
		captain->GetAnimationsList()[eCaptainState::SIT_ON_SHIELD]->Render(spriteData);
	}
	break;
	case eCaptainState::SWING:
	{
		captain->GetAnimationsList()[eCaptainState::SWING]->Render(spriteData);
	}
	break;
	case eCaptainState::WADE:
	{
		captain->GetAnimationsList()[eCaptainState::WADE]->Render(spriteData);
	}
	break;
	case eCaptainState::SHIELD_TOP:
	{
		captain->GetAnimationsList()[eCaptainState::SHIELD_TOP]->Render(spriteData);
	}
	break;
	case eCaptainState::HURT:
	{
		captain->GetAnimationsList()[eCaptainState::HURT]->Render(spriteData);
	}
	break;
	case eCaptainState::DEAD:
	{
		captain->GetAnimationsList()[eCaptainState::DEAD]->Render(spriteData);
	}
	break;
	case eCaptainState::DASH:
	{
		if (captain->GetAnimationsList()[eCaptainState::DASH]->GetCurFrame() == 0)
			captain->GetAnimationsList()[eCaptainState::DASH]->SetCurFrame(1);
		captain->GetAnimationsList()[eCaptainState::DASH]->Render(spriteData);
	}
	break;
	}
}
