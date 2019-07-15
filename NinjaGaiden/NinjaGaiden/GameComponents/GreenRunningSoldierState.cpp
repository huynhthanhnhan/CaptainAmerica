#include "GreenRunningSoldierState.h"
#include "Grid.h"

GreenRunningSoldierState::GreenRunningSoldierState(GreenRunningSoldier * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

GreenRunningSoldierState::~GreenRunningSoldierState()
{
}

void GreenRunningSoldierState::Jump()
{
}

void GreenRunningSoldierState::Crouch()
{
}

void GreenRunningSoldierState::JumpAttack()
{
}

void GreenRunningSoldierState::Climb()
{
}

void GreenRunningSoldierState::Idle()
{
}

void GreenRunningSoldierState::Attack()
{
}

void GreenRunningSoldierState::Walk()
{
}

void GreenRunningSoldierState::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsEnemyInCamera(enemy) == true)
	{
		enemy->SetActive(true);

		if (enemy->GetMaxPosX() > 0 && enemy->GetMinPosX() > 0)
		{
			if (enemy->GetPositionX() > enemy->GetMaxPosX())
			{
				enemy->SetSpeedX(-GREEN_RUNNING_SOLDIER_WALKING_SPEED);
				enemy->TurnLeft();
			}
			if (enemy->GetPositionX() < enemy->GetMinPosX())
			{
				enemy->SetSpeedX(GREEN_RUNNING_SOLDIER_WALKING_SPEED);
				enemy->TurnRight();
			}
		}

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
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		enemy->SetActive(false);
	}
}

void GreenRunningSoldierState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width = GREEN_RUNNING_SOLDIER_SPRITE_WIDTH;
		spriteEnemyData.height = GREEN_RUNNING_SOLDIER_SPRITE_HEIGHT;
		spriteEnemyData.x = enemy->GetPositionX();
		spriteEnemyData.y = enemy->GetPositionY();


		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();
	}
	switch (enemystate)
	{
	case GREEN_RUNNING_SOLDIER_ANI_IDLE:
	{
		enemy->GetAnimationsList()[GREEN_RUNNING_SOLDIER_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case GREEN_RUNNING_SOLDIER_ANI_WALKING:
	{
		enemy->GetAnimationsList()[GREEN_RUNNING_SOLDIER_ANI_WALKING]->Render(spriteEnemyData);
	}
	break;
	}
}

