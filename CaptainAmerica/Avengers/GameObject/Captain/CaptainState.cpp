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
			if (captain->IsGrounded())
			{
				captain->SetIsGrounded(false);
				captain->SetSpeedY(CAPTAIN_AMERICA_JUMP_SPEED_Y);
				newState = JUMP;
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
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
			captain->SetSpeedX(0);
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
			if (captain->GetPositionY() > captain->currentPositionBeforeJump + captain->heightToRoll)
			{
				captain->SetSpeedY(0);
				captain->SetSpeedX(0);
				newState = SIT_ON_SHIELD;
			}
			if (captain->IsGrounded())
			{
				captain->SetSpeedX(0);
				newState = IDLE;
			}
			break;
		case JumpControl:
			if (captain->GetSpeedY() > captain->maxJumpSpeed)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
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
			if (captain->isThrowing == false)
			{
				captain->SetSpeedX(0);
				captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->SetCurFrame(0);
				newState = IDLE;
			}
			
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->SetCurFrame(0);
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
					captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->SetCurFrame(0);
					newState = JUMP;
				}
			}
			break;
		case DashControl:
			break;
		case ThrowControl:
			if (captain->isThrowing == false)
			{
				captain->SetSpeedX(0);
				newState = IDLE;
			}
			break;
		}
		break;
	case ROLL:
		break;
	case KICK:
		switch (control)
		{
		case NoneControl:
			if (captain->IsGrounded())
			{
				captain->SetSpeedX(0);
				newState = IDLE;
			}
			break;
		case ThrowControl:
			break;
		case UpControl:
		case DownControl:
		case JumpControl:
		case DashControl:
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
		switch (control)
		{
		case NoneControl:
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
			break;
		case JumpControl:
			break;
		case DashControl:
			break;
		case ThrowControl:
			break;
		default:
			break;
		}
		break;
	case SWING:
		break;
	case WADE:
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			break;
		case LeftControl:
		case RightControl:
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			break;
		case UpControl:
			break;
		case DownControl:
			newState = DIVE;
			break;
		case JumpControl:
			if (captain->GetSpeedY() > 0.4)
			{
				captain->isFalling = true;
			}
			if (!captain->isFalling && captain->GetSpeedY() <= 0.4)
			{
				captain->SetSpeedY(captain->GetSpeedY() + 0.05);
				if (captain->IsGrounded() || captain->isWading)
				{
					captain->isWading = false;
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
		if (captain->IsGrounded())
			newState = IDLE;
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
		switch (control)
		{
		case NoneControl:
			captain->SetSpeedX(0);
			newState = IDLE;
			break;
		case LeftControl:
			break;
		case RightControl:
			break;
		case UpControl:
			break;
		case DownControl:
			break;
		case JumpControl:
			break;
		case DashControl:
			break;
		case ThrowControl:
			break;
		default:
			break;
		}
		break;
	case DIVE:
		switch (control)
		{
		case NoneControl:
		case LeftControl:
		case RightControl:
		case UpControl:
			newState = WADE;
			break;
		case DownControl:
			break;
		case JumpControl:
			break;
		case DashControl:
			break;
		case ThrowControl:
			break;
		default:
			break;
		}
		break;
	}
	captain->SetState(newState);
}

void CaptainState::Update(DWORD dt)
{
	if (captain->IsGrounded())
	{
		captain->isFalling = false;
	}
	if (captain->isWading && captain->GetEnumState() != DIVE)
		captain->SetState(WADE);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<Enemy* > enemies = Grid::GetInstance()->GetEnemies();

#pragma region	Collide with Brick and River
	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();

	captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_AMERICA_GRAVITY);

	coEvents.clear();
	captain->SetDt(dt);
	captain->CheckMapCollision(tiles, coEvents);

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

		float moveX = min_tx * captain->GetSpeedX() * dt;
		float moveY = min_ty * captain->GetSpeedY() * dt;

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
				captain->isWading = true;
				captain->SetPositionX(captain->GetPositionX() - 0.75);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion

#pragma region Colide with enemy
	coEvents.clear();
	captain->SetDt(dt);
	captain->CheckEnemyCollision(enemies, coEvents);

	if (coEvents.size() > 0)
	{
		float min_tx, min_ty, nx = 0, ny;

		captain->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * captain->GetSpeedX() * dt + nx * 3;
		float moveY = min_ty * captain->GetSpeedY() * dt + ny * 0.4;

		captain->SetPositionX(captain->GetPositionX() + moveX * 2);
		captain->SetPositionY(captain->GetPositionY() + moveY);

		//if (nx != 0) captain->SetSpeedX(captain->GetSpeedX() * -1);
		//if (ny != 0) captain->SetSpeedY(captain->GetSpeedY() * -1);

		if (coEventsResult[0]->collisionID == 0)
		{
			{
				captain->SetState(HURT);
			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
}


void CaptainState::Render()
{
	eCaptainState state = this->state;

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
	int count = 0;

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
		DebugOut(L"current pos: %f\n", captain->currentPositionBeforeJump);
		//if (captain->GetSpeedY() >= 0.25 || captain->isFalling)
		if (captain->GetPositionY() > captain->currentPositionBeforeJump + captain->heightToRoll)
		{
			Shield::GetInstance()->SetState(NO_SHIELD);
			if (captain->GetAnimationsList()[eCaptainState::JUMP]->GetCurFrame() == 4)
				captain->GetAnimationsList()[eCaptainState::JUMP]->SetCurFrame(2);
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
		if(captain->IsGrounded())
			captain->GetAnimationsList()[eCaptainState::WALK]->Render(spriteData);
		else
		{
			captain->GetAnimationsList()[eCaptainState::JUMP]->SetCurFrame(0);
			captain->GetAnimationsList()[eCaptainState::JUMP]->Render(spriteData);
		}
	}
	break;

	case eCaptainState::THROW_SHIELD:
	{
		if (captain->isThrowing)
		{
			if (captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->GetCurFrame() == 4)
				captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->SetCurFrame(2);
			DebugOut(L"Rendering: %d \n", captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->GetCurFrame());
		}
		else
		{
			/*
			DebugOut(L"Rendering: %d \n", captain->GetAnimationsList()[eCaptainState::THROW_SHIELD]->GetCurFrame());*/
		}
			
		
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
	case eCaptainState::DIVE:
	{
		captain->GetAnimationsList()[eCaptainState::DIVE]->Render(spriteData);
	}
	break;
	}
}