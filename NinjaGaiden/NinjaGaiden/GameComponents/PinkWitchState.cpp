#include "PinkWitchState.h"
#include "Grid.h"

PinkWitchState::PinkWitchState(PinkWitch * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

PinkWitchState::~PinkWitchState()
{
}

void PinkWitchState::Jump()
{
}

void PinkWitchState::Crouch()
{
}

void PinkWitchState::JumpAttack()
{
}

void PinkWitchState::Climb()
{
}

void PinkWitchState::Idle()
{
}

void PinkWitchState::Attack()
{
}

void PinkWitchState::Walk()
{
}

void PinkWitchState::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsEnemyInCamera(enemy) == true)
	{	
		if (enemy->GetPositionX() > enemy->GetMaxPosX())
		{
			enemy->SetSpeedX(-PINK_WITCH_SPEED);
			enemy->TurnLeft();
		}
		if (enemy->GetPositionX() < enemy->GetMinPosX())
		{
			enemy->SetSpeedX(PINK_WITCH_SPEED);
			enemy->TurnRight();
		}
		/*if (Ninja::GetInstance()->GetPositionX() < enemy->GetPositionX() - 40 || Ninja::GetInstance()->GetPositionX() > enemy->GetPositionX() + 40)
		{
			if (enemy->GetPositionX() > Ninja::GetInstance()->GetPositionX())
			{
				enemy->TurnLeft();
			}
			else
			{
				enemy->TurnRight();
			}
		}*/
		enemy->SetActive(true);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		vector<Tile *> tiles = Grid::GetInstance()->GetCollisionTiles();

		enemy->SetSpeedY(enemy->GetSpeedY() - NINJA_GRAVITY);

		coEvents.clear();
		enemy->SetDt(dt);
		enemy->CalcPotentialCollisions(tiles, coEvents);

		if (coEvents.size() == 0)
		{
			float moveX = trunc(enemy->GetSpeedX()* dt);
			float moveY = trunc(enemy->GetSpeedY()* dt);

			enemy->SetPositionX(enemy->GetPositionX() + moveX);
			enemy->SetPositionY(enemy->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			enemy->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * enemy->GetSpeedX() * dt + nx * 0.4;
			float moveY = min_ty * enemy->GetSpeedY() * dt + ny * 0.4;

			enemy->SetPositionX(enemy->GetPositionX() + moveX);
			enemy->SetPositionY(enemy->GetPositionY() + moveY);


			if (nx != 0) enemy->SetSpeedX(0);
			if (ny != 0) enemy->SetSpeedY(0);		
		}	

		/*if (enemy->GetMovingDistance() > 0)
		{
			enemy->SetDistance(enemy->GetDistance() + enemy->GetSpeedX() * dt);

			if (enemy->IsLeft() == true)
			{
 				if (abs(enemy->GetDistance()) >= enemy->GetMovingDistance())
				{
					enemy->TurnRight();
					enemy->ResetDistance();
				}
			}
			else if (enemy->IsLeft() == false)
			{
				if (enemy->GetDistance() >= enemy->GetMovingDistance())
				{
					enemy->TurnLeft();
					enemy->ResetDistance();
				}
			}
		}*/

		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];	
	}
	else
	{
		enemy->SetActive(false);
	}
}

void PinkWitchState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width = PINK_WITCH_SPRITE_WIDTH;
		spriteEnemyData.height = PINK_WITCH_SPRITE_HEIGHT;
		spriteEnemyData.x = enemy->GetPositionX();
		spriteEnemyData.y = enemy->GetPositionY();
		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();
	}
	switch (enemystate)
	{
	case  PINK_WITCH_ANI_IDLE:
	{
		enemy->GetAnimationsList()[PINK_WITCH_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case  PINK_WITCH_ANI_WALKING:
	{
		enemy->GetAnimationsList()[PINK_WITCH_ANI_WALKING]->Render(spriteEnemyData);
	}
	break;
	}
}

