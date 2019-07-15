#include "NinjaSate.h"
#include "Sword.h"
#include <math.h>
#include "Bullet.h"

NinjaSate::NinjaSate(Ninja * ninja, int states)
{
	this->ninja = ninja;
	this->states = states;
}

NinjaSate::~NinjaSate()
{
}

void NinjaSate::Jump()
{
	int state = this->states;

	switch (state)
	{
	case NINJA_ANI_STANDING_ATTACKING:
	case NINJA_ANI_CROUCHING_ATTACKING:
	case NINJA_ANI_CROUCHING:
	case NINJA_ANI_JUMPING:
	case NINJA_ANI_JUMPING_ATTACKING:
		break;
	case NINJA_ANI_IDLE:
	case NINJA_ANI_WALKING:
	{
		if (ninja->IsGrounded())
		{
			ninja->SetIsGrounded(false);
			ninja->SetSpeedY(NINJA_JUMP_SPEED_Y);
			ninja->SetState(ninja->GetJumpingState());
		}
	}
	break;
	case NINJA_ANI_CLIMBING :
		ninja->SetIsGrounded(false);
		ninja->SetSpeedY(NINJA_JUMP_SPEED_Y);
		ninja->SetState(ninja->GetJumpingState());
		ninja->SetSpeedX(NINJA_WALKING_SPEED * (ninja->IsLeft() == true ? 1 : -1));
		break;
	}
}

void NinjaSate::Crouch()
{
	int state = this->states;

	switch (state)
	{
	case NINJA_ANI_STANDING_ATTACKING:
	case NINJA_ANI_CROUCHING_ATTACKING:
	case NINJA_ANI_CROUCHING:
	case NINJA_ANI_JUMPING:
	case NINJA_ANI_JUMPING_ATTACKING:
		break;
	case NINJA_ANI_IDLE:
	{
		ninja->SetIsCrouching(true);
		ninja->SetState(ninja->GetCrouchingState());
	}
	break;
	case NINJA_ANI_WALKING:
	{
		ninja->SetSpeedX(0);
		ninja->SetIsCrouching(true);
		ninja->SetState(ninja->GetCrouchingState());
	}
	break;
	}
}

void NinjaSate::JumpAttack()
{
	int state = this->states;
	if (NINJA_ANI_JUMPING == state)
	{
		ninja->SetIsGrounded(false);
		ninja->SetState(ninja->GetJumpAttackState());
	}
}

void NinjaSate::Climb()
{
	int state = this->states;

	switch (state)
	{
	case NINJA_ANI_STANDING_ATTACKING:
	case NINJA_ANI_CROUCHING:
	case NINJA_ANI_JUMPING_ATTACKING:
		break;
	case NINJA_ANI_IDLE:
	{
		ninja->SetState(ninja->GetClimbState());
	}
	break;
	case NINJA_ANI_CROUCHING_ATTACKING:
		break;
	case NINJA_ANI_WALKING:
	{
		ninja->SetSpeedX(0);
		ninja->SetState(ninja->GetClimbState());
	}
	break;
	}
}

void NinjaSate::Idle()
{
	int state = this->states;
	ninja->SetColliderDemension(24, 45);
	switch (state)
	{
	case NINJA_ANI_STANDING_ATTACKING:
	case NINJA_ANI_IDLE:
	case NINJA_ANI_JUMPING_ATTACKING:
	case NINJA_ANI_JUMPING_ATTACKED:
		break;
	case NINJA_ANI_CROUCHING:
	{
		ninja->SetIsCrouching(false);
		ninja->SetState(ninja->GetIdleState());
	}
	break;
	case NINJA_ANI_CROUCHING_ATTACKING:
		break;
	case NINJA_ANI_WALKING:
	{
		ninja->SetSpeedX(0);
		ninja->SetState(ninja->GetIdleState());
	}
	break;
	}
}

void NinjaSate::Attack()
{
	int state = this->states;

	switch (state)
	{
	case NINJA_ANI_STANDING_ATTACKING:
		break;
	case NINJA_ANI_IDLE:
	case NINJA_ANI_CROUCHING:
	{
		ninja->SetState(ninja->GetAttackingState());
		break;
	}
	break;
	case NINJA_ANI_WALKING:
	{
		ninja->SetSpeedX(0);
		ninja->SetState(ninja->GetAttackingState());
	}
	break;
	case NINJA_ANI_JUMPING_ATTACKING:
	{
		ninja->SetState(ninja->GetAttackingState());
		break;
	}
	break;
	}
	
}

void NinjaSate::Walk()
{
	int state = this->states;
	ninja->SetColliderDemension(22, 45);
	switch (state)
	{
	case NINJA_ANI_STANDING_ATTACKING:
	case NINJA_ANI_CROUCHING_ATTACKING:
	case NINJA_ANI_CROUCHING:
	case NINJA_ANI_JUMPING:
	case NINJA_ANI_JUMPING_ATTACKING:
		break;
	case NINJA_ANI_IDLE:
	{
		ninja->SetSpeedX(NINJA_WALKING_SPEED * (ninja->IsLeft() ? -1 : 1));
		ninja->SetState(ninja->GetWalkingState());
	}
	break;
	case NINJA_ANI_WALKING:
	{
		ninja->SetSpeedX(NINJA_WALKING_SPEED * (ninja->IsLeft() ? -1 : 1));
	}
	break;
	}
}

void NinjaSate::Throw()
{
	int state = this->states;
	switch (state)
	{
		case NINJA_ANI_CROUCHING:
		case NINJA_ANI_JUMPING:
		case NINJA_ANI_IDLE:
		{
			ninja->SetState(ninja->GetThrowingState());
		}
		break;
	}
}
void NinjaSate::Attacked()
{
	ninja->SetState(ninja->GetAttackedState());
}
bool ShuriKenTurn = false;
void NinjaSate::Update(DWORD dt)
{
	#pragma region Get enemies and create event
	int state = this->states;
	switch (state)
	{
	case NINJA_ANI_JUMPING:
	{
		if (ninja->IsGrounded())
		{
			ninja->SetState(ninja->GetIdleState());
		}
		if (ninja->GetPositionY() >= TiledMap::GetInstance()->GetHeight() + 20)
		{
			ninja->SetSpeedY(ninja->GetSpeedY() - NINJA_GRAVITY);
		}
	}
	break;
	case NINJA_ANI_JUMPING_ATTACKING:
	{
		if (ninja->IsGrounded())
		{
			ninja->SetState(ninja->GetIdleState());
		}
	}
	break;
	default:
		break;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<Enemy* > enemies = Grid::GetInstance()->GetEnemies();

	if (Game::GetInstance()->GetStage() == Stage::STAGE_BOSS)
	{
		enemies = Grid::GetInstance()->GetAllEnemies();
	}
	#pragma endregion

	#pragma region sword and shuriken collide with enemy
	if (state == NINJA_ANI_STANDING_ATTACKING || state == NINJA_ANI_JUMPING_ATTACKING || state == NINJA_ANI_CROUCHING_ATTACKING)
	{
		int direction = (ninja->IsLeft() == true) ? -1 : 1;
		Sword * sword = Sword::GetInstance();

		sword->SetAttackTime(dt);
		if (sword->GetAttackTime() <= 0)
		{
			sword->SetPosition(ninja->GetPositionX(), ninja->GetPositionY() - ninja->GetHeight() / 4, dt);
			sword->SetSpeedX(ninja->GetSpeedX());

			sword->CalcPotentialCollisionsAttackingEnemy(enemies, coEvents);

			if (coEvents.size() > 0)
			{
				sword->ResetAttackTime();
			}

			vector<Bullet*> bullets = Grid::GetInstance()->GetEnemyBullet();

			sword->CalcPotentialNinjaSwordWithBullet(bullets, coEvents);
		}	
	}

	vector <Shuriken* > shurikens = ninja->GetShuriken();

	if (state == NINJA_ANI_THROWING)
	{
		ninja->SetThrowing(true);
		vector<LPCOLLISIONEVENT> coEvents;
		int direction = (ninja->IsLeft() == true) ? -1 : 1;
		if (shurikens.size() > 0)
		{
			if (shurikens[0]->IsActive() == false)
			{
				shurikens[0]->CreateShuriken(ninja->GetPositionX() + ninja->GetWidth()*direction, ninja->GetPositionY(), dt, ninja->IsLeft());
			} 
		}
		///// Ném nhiều phi tiêu
		/*if (shurikens.size() > 0)
		{
			if (shurikens[0]->IsActive() == false)
			{
				shurikens[0]->CreateShuriken(ninja->GetPositionX() + ninja->GetWidth()*direction, ninja->GetPositionY(), dt, ninja->IsLeft());
				shurikens[1]->CreateShuriken(ninja->GetPositionX() + ninja->GetWidth()*direction + 10*direction, ninja->GetPositionY(), dt, ninja->IsLeft());
				shurikens[2]->CreateShuriken(ninja->GetPositionX() + ninja->GetWidth()*direction + 20*direction, ninja->GetPositionY(), dt, ninja->IsLeft());
			}
		}*/
	}
	#pragma endregion

	#pragma region	Collide with brick
	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();
	if (state != NINJA_ANI_CLIMBING)
	{
		ninja->SetSpeedY(ninja->GetSpeedY() - NINJA_GRAVITY);
	}

	coEvents.clear();
	ninja->SetDt(dt);
	ninja->CalcPotentialCollisions(tiles, coEvents);

	if (coEvents.size() == 0)
	{
		float moveX = trunc(ninja->GetSpeedX()* dt);
		float moveY = trunc(ninja->GetSpeedY()* dt);
		ninja->SetPositionX(ninja->GetPositionX() + moveX);
		ninja->SetPositionY(ninja->GetPositionY() + moveY);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		ninja->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * ninja->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * ninja->GetSpeedY() * dt + ny * 0.4;

		ninja->SetPositionX(ninja->GetPositionX() + moveX);
		ninja->SetPositionY(ninja->GetPositionY() + moveY);


		if (nx != 0) ninja->SetSpeedX(0);
		if (ny != 0) ninja->SetSpeedY(0);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				ninja->SetIsGrounded(true);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	#pragma endregion

	#pragma region Collide with enemy

	if (ninja->IsUntouchable() == false)
	{
		coEvents.clear();
		ninja->SetDt(dt);
		ninja->CalcPotentialCollisionsWithEnemy(enemies, coEvents);

		if (coEvents.size() > 0)
		{
			float min_tx, min_ty, nx = 0, ny;

			ninja->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * ninja->GetSpeedX() * dt + nx * 3;
			float moveY = min_ty * ninja->GetSpeedY() * dt + ny * 0.4;

			ninja->SetPositionX(ninja->GetPositionX() + moveX * 2);
			ninja->SetPositionY(ninja->GetPositionY() + moveY);

			/*if (ninja->IsGrounded() == false)
			{
			}*/
			if (nx != 0) ninja->SetSpeedX(ninja->GetSpeedX() * -1);
			if (ny != 0) ninja->SetSpeedY(ninja->GetSpeedY() * -1);

			if (coEventsResult[0]->collisionID == 1)
			{
				if (ny == 1)
				{
					ninja->SetIsGrounded(true);
				}
			}
			ninja->SetUntouchable(true);

		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		ninja->SetUntouchableTime(ninja->GetUntouchableTime() - dt);
		if (ninja->GetUntouchableTime() <= 0)
		{
			ninja->SetUntouchableTime(2000);
			ninja->SetUntouchable(false);
		}
	}
	#pragma endregion

	#pragma region Collide with enemy bullet
	vector<Bullet* > bullets = Grid::GetInstance()->GetEnemyBullet();
	if (ninja->IsUntouchable() == false)
	{
		coEvents.clear();
		ninja->SetDt(dt);
		ninja->NinjaCollideWithEnemyBullet(bullets, coEvents);

		if (coEvents.size() > 0)
		{
			float min_tx, min_ty, nx = 0, ny;

			ninja->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * ninja->GetSpeedX() * dt + nx * 3;
			float moveY = min_ty * ninja->GetSpeedY() * dt + ny * 0.4;

			ninja->SetPositionX(ninja->GetPositionX() + moveX * 4);
			ninja->SetPositionY(ninja->GetPositionY() + moveY);

			if (nx != 0) ninja->SetSpeedX(ninja->GetSpeedX() * -1);
			if (ny != 0) ninja->SetSpeedY(ninja->GetSpeedY() * -1);

			if (coEventsResult[0]->collisionID == 1)
			{
				if (ny == 1)
				{
					ninja->SetIsGrounded(true);
				}
			}
			ninja->SetUntouchable(true);

		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		ninja->SetUntouchableTime(ninja->GetUntouchableTime() - dt);
		if (ninja->GetUntouchableTime() <= 0)
		{
			ninja->SetUntouchableTime(400);
			ninja->SetUntouchable(false);
		}
	}
	#pragma endregion

	#pragma	region Collide with item
	vector<GameItem * > gameitems = Grid::GetInstance()->GetGameItem();
	ninja->SetDt(dt);
	ninja->CalcPotentialCollisionsWithGameItem(gameitems);
	#pragma endregion

	#pragma region Ninja death

	if (ninja->GetPositionY() < 0)
	{
		NinjaDeath();
	}
	#pragma endregion

	#pragma region Update shuriken after throwing
	shurikens = ninja->GetShuriken();

	if (shurikens.size() > 0)
	{
		if (ninja->IsLeft() == true && shurikens[0]->IsActive() == true)
		{
			//if (abs(shurikens[0]->GetDistance()) >= 150 && ShuriKenTurn == false)
			if (abs(shurikens[0]->GetDistance()) >= 150)
			{
				ninja->DescreaseShuriken();
				/*shurikens[0]->SetSpeedX(shurikens[0]->GetSpeedX() * (-1));
				ShuriKenTurn = true;*/
			}
			else
			{
				shurikens[0]->Update(dt);
			}
		}
		else if (ninja->IsLeft() == false && shurikens[0]->IsActive() == true)
		{
			//if (shurikens[0]->GetDistance() >= 150 && ShuriKenTurn == false)
			if (shurikens[0]->GetDistance() >= 150 )
			{
				ninja->DescreaseShuriken();
				/*shurikens[0]->SetSpeedX(shurikens[0]->GetSpeedX() * (-1));
				ShuriKenTurn = true;*/
			}
			else
			{
				shurikens[0]->Update(dt);
			}
		}

		//////// Ném nhiều phi tiêu
		/*if (ninja->IsLeft() == true && shurikens[0]->IsActive() == true)
		{
			for (size_t i = 0; i < shurikens.size(); i++)
			{
				if (abs(shurikens[i]->GetDistance()) >= 150)
				{
					ninja->DescreaseShuriken();
				}
				else
				{
					shurikens[i]->Update(dt);
				}
			}
		}
		else if (ninja->IsLeft() == false && shurikens[0]->IsActive() == true)
		{
			for (size_t i = 0; i < shurikens.size(); i++)
			{
				if (shurikens[i]->GetDistance() >= 150)
				{
					ninja->DescreaseShuriken();
				}
				else
				{
					shurikens[i]->Update(dt);
				}
			}
		}*/
	}
	#pragma endregion
}
void NinjaSate::NinjaDeath()
{
	ninja->SetPositionX(100);
	ninja->SetPositionY(100);
	Viewport::GetInstance()->Reset();
	Game::GetInstance()->GetHud()->Reset();
}

void NinjaSate::Render()
{
	int state = this->states;

	SpriteData spriteData;
	if (this->ninja != NULL)
	{
		spriteData.width = NINJA_SPRITE_WIDTH;
		spriteData.height = NINJA_SPRITE_HEIGHT;
		spriteData.x = ninja->GetPositionX();
		spriteData.y = ninja->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = ninja->IsLeft();
		spriteData.isFlipped = ninja->IsFlipped();
	}

	switch (state)
	{
	case NINJA_ANI_STANDING_ATTACKING:
	{
		if (ninja->IsCrouching())
		{
			ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Render(spriteData);

			if (ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->IsDone())
			{
				ninja->GetAnimationsList()[NINJA_ANI_CROUCHING_ATTACKING]->Reset();
				ninja->SetIsCrouching(true);
				ninja->SetState(ninja->GetCrouchingState());
			}
		}
		else
		{
			ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Render(spriteData);
			if (ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->IsDone())
			{
				ninja->GetAnimationsList()[NINJA_ANI_STANDING_ATTACKING]->Reset();
				ninja->SetState(ninja->GetIdleState());
			}
		}
	}
	break;
	case NINJA_ANI_IDLE:
	{
		ninja->GetAnimationsList()[NINJA_ANI_IDLE]->Render(spriteData);
	}
	break;
	case NINJA_ANI_CROUCHING:
	{
		ninja->GetAnimationsList()[NINJA_ANI_CROUCHING]->Render(spriteData);
	}
	break;
	case NINJA_ANI_JUMPING:
	{
		ninja->GetAnimationsList()[NINJA_ANI_JUMPING]->Render(spriteData);
	}
	break;
	case NINJA_ANI_CLIMBING:
	{
		ninja->GetAnimationsList()[NINJA_ANI_CLIMBING]->Render(spriteData);

		if (ninja->GetAnimationsList()[NINJA_ANI_CLIMBING]->IsDone())
		{
			ninja->GetAnimationsList()[NINJA_ANI_CLIMBING]->Reset();
			ninja->SetState(ninja->GetIdleState());
		}
	}
	break;
	case NINJA_ANI_WALKING:
	{
		ninja->GetAnimationsList()[NINJA_ANI_WALKING]->Render(spriteData);
	}
	break;
		case NINJA_ANI_JUMPING_ATTACKING:
		{
			ninja->GetAnimationsList()[NINJA_ANI_JUMPING_ATTACKING]->Render(spriteData);

			if (ninja->GetAnimationsList()[NINJA_ANI_JUMPING_ATTACKING]->IsDone())
			{
				ninja->GetAnimationsList()[NINJA_ANI_JUMPING_ATTACKING]->Reset();
				ninja->SetState(ninja->GetJumpingState());
			}
		}
		break;
		case NINJA_ANI_THROWING:
		{
			ninja->GetAnimationsList()[NINJA_ANI_THROWING]->Render(spriteData);
		}
		break;
		case NINJA_ANI_JUMPING_ATTACKED:
			ninja->GetAnimationsList()[NINJA_ANI_JUMPING_ATTACKED]->Render(spriteData);
			break;
	}
	
	vector <Shuriken* > shurikens = ninja->GetShuriken();
	//// ném nhiều phi tiêu 
	/*for (size_t i = 0; i < shurikens.size(); i++)
	{
		shurikens[i]->Render();
	}*/

	if (shurikens.size() > 0)
	{
		shurikens[0]->Render();
	}
}
