#include "GreenCanonSoldierState.h"
#include "Grid.h"

GreenCanonSoldierState::GreenCanonSoldierState(GreenCanonSoldier * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

GreenCanonSoldierState::~GreenCanonSoldierState()
{
}

void GreenCanonSoldierState::Jump()
{
}

void GreenCanonSoldierState::Crouch()
{
}

void GreenCanonSoldierState::JumpAttack()
{
}

void GreenCanonSoldierState::Climb()
{
}

void GreenCanonSoldierState::Idle()
{
}

void GreenCanonSoldierState::Attack()
{
}

void GreenCanonSoldierState::Walk()
{
}

void GreenCanonSoldierState::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsEnemyInCamera(enemy) == true)
	{
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
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		enemy->SetActive(false);
	}
}

void GreenCanonSoldierState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width = BROWN_BIRD_SPRITE_WIDTH;
		spriteEnemyData.height = BROWN_BIRD_SPRITE_HEIGHT;
		spriteEnemyData.x = enemy->GetPositionX();
		spriteEnemyData.y = enemy->GetPositionY();


		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();
	}
	switch (enemystate)
	{
	case BROWN_BIRD_ANI_IDLE:
	{
		enemy->GetAnimationsList()[BROWN_BIRD_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case BROWN_BIRD_ANI_WALKING:
	{
		enemy->GetAnimationsList()[BROWN_BIRD_ANI_WALKING]->Render(spriteEnemyData);
	}
	break;
	}
}

