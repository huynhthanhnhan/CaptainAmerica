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

void CaptainState::SetNewState(eCaptainState state, eController control)
{
	eCaptainState newState = state;
	switch (state)
	{
	case IDLE:
		switch (control)
		{
		case NoneControl: 
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			newState = WALK;
			break;
		case UpControl:
			captain->SetIsShieldUp(true);
			newState = SHIELD_TOP;
			break;
		case DownControl:
			captain->SetIsCrouching(true);
			newState = CROUCH;
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded())
				{
					captain->SetIsGrounded(false);
					captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			captain->isThrowing = true;
			newState = THROW_SHIELD;
			break;
		default:
			break;
		}
		break;
	case WALK:
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			newState = IDLE;
			break;
		case LeftControl:
		case RightControl:
		case UpControl:
		case DownControl:
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded())
				{
					captain->SetIsGrounded(false);
					captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			captain->isThrowing = true;
			newState = THROW_SHIELD;
			break;
		}
		break;
	case JUMP:
		switch (control)
		{
		case NoneControl:
			if (captain->IsGrounded())
			{
				captain->SetSpeedX(0);
				newState = IDLE;
			}
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			if (captain->IsGrounded())
				newState = WALK;
			break;
		case UpControl:
		case DownControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->SetSpeedY(0);
				newState = SIT_ON_SHIELD;
			}
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded())
				{
					captain->SetIsGrounded(false);
					captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			captain->SetIsGrounded(false);
			newState = KICK;
			break;
		default:
			break;
		}
		break;
	case CROUCH:
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			newState = IDLE;
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			newState = WALK;
			break;
		case UpControl:
			newState = IDLE;
			break;
		case DownControl:
			break;
		case JumpControl:
			captain->SetPositionY(captain->GetPositionY() - 0.5);
			break;
		case DashControl:
			break;
		case ThrowControl:
			newState = CROUCH_HIT;
			break;
		}
		break;
	case THROW_SHIELD:
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			newState = IDLE;
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			newState = WALK;
			break;
		case UpControl:
			newState = SHIELD_TOP;
			break;
		case DownControl:
			newState = CROUCH;
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded())
				{
					captain->SetIsGrounded(false);
					captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			newState = STAND_HIT;
			break;
		}
		break;
	case ROLL:
		break;
	case KICK:
		switch (control)
		{
		case NoneControl:
		case UpControl:
		case DownControl:
		case JumpControl:
		case DashControl:
		case ThrowControl:
			newState = JUMP;
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			break;
		}
		break;
	case STAND_HIT:
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			newState = IDLE;
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			break;
		case UpControl:
			break;
		case DownControl:
			newState = CROUCH_HIT;
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded())
				{
					captain->SetIsGrounded(false);
					captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			break;
		}
		break;
	case CROUCH_HIT:
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			newState = IDLE;
			break;
		case LeftControl:
		case RightControl:
		case UpControl:
		case DownControl:
			newState = STAND_HIT;
			break;
		case DashControl:
			break;
		case ThrowControl:
			break;
		case JumpControl:
			captain->SetPositionY(captain->GetPositionY() - 0.5);
			break;
		}
		break;
	case SIT_ON_SHIELD:
		break;
	case SWING:
		break;
	case WADE:
		switch (control)
		{
		case NoneControl:
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			break;
		case UpControl:
			break;
		case DownControl:
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded())
				{
					captain->SetIsGrounded(false);
					captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			break;
		}
		break;
	case SHIELD_TOP:
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			newState = IDLE;
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			newState = WALK;
			break;
		case UpControl:
			break;
		case DownControl:
			newState = IDLE;
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded())
				{
					captain->SetIsGrounded(false);
					captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			captain->isThrowing = true;
			newState = THROW_SHIELD;
			break;
		}
		break;
	case HURT:
		break;
	case DEAD:
		break;
	case DASH:
		break;
	default:
		break;
	}
	captain->SetState(newState);
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
		captain->SetState(IDLE);
	}
	break;
	case eCaptainState::WALK:
	{
		captain->SetSpeedX(0);
		captain->SetState(IDLE);
	}
	break;
	case eCaptainState::DASH:
	{
		captain->SetSpeedX(0);
		captain->SetState(IDLE);
	}
	case eCaptainState::THROW_SHIELD:
	case eCaptainState::SHIELD_TOP:
		captain->SetState(IDLE);
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
		captain->SetState(WALK);
	}
	break;
	case eCaptainState::WALK:
	{
		captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
	}
	break;
	case eCaptainState::THROW_SHIELD:
		captain->SetState(IDLE);
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
		
		break;
	case eCaptainState::IDLE:
	case eCaptainState::WALK:
	{
		if (captain->IsGrounded())
		{
			captain->SetIsGrounded(false);
			captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
			captain->SetState(JUMP);
		}
	}
	break;
	case eCaptainState::WADE:
	{
		if (captain->isWading)
		{
			captain->isWading = false;
			captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
			captain->SetState(JUMP);
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
			captain->SetState(CROUCH);
		}
		break;
		case eCaptainState::WALK:
		case eCaptainState::CROUCH_HIT:
		{
			captain->SetSpeedX(0);
			captain->SetIsCrouching(true);
			captain->SetState(CROUCH);
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
		captain->SetState(THROW_SHIELD);
	}
	break;
	case eCaptainState::JUMP:
		captain->SetState(JUMP);
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
		captain->SetState(KICK);
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
	captain->SetState(CROUCH_HIT);
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
	captain->SetState(WADE);
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
		captain->SetState(SHIELD_TOP);
	}
	break;
	case eCaptainState::WALK:
	{
		captain->SetSpeedX(0);
		captain->SetIsShieldUp(true);
		captain->SetState(SHIELD_TOP);
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
			captain->SetState(DASH);
			break;

	}
}

void CaptainState::Update(DWORD dt)
{
	if (captain->IsGrounded())
	{
		captain->isFalling = false;
	}
	if (captain->isWading)
		captain->SetState(WADE);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

#pragma region	Collide with brick
	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();
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
