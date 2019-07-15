#include "BossState.h"
#include "Grid.h"

BossState::BossState(Boss * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

BossState::~BossState()
{
}

void BossState::Jump()
{
}

void BossState::Crouch()
{
}

void BossState::JumpAttack()
{
}

void BossState::Climb()
{
}

void BossState::Idle()
{
}

void BossState::Attack()
{
}

void BossState::Walk()
{
}

void BossState::Update(DWORD dt)
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
		enemy->SetSpeedX(0);
	}
}

void BossState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width = BOSS_SPRITE_WIDTH;
		spriteEnemyData.height = BOSS_SPRITE_HEIGHT;
		spriteEnemyData.x = enemy->GetPositionX();
		spriteEnemyData.y = enemy->GetPositionY();


		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();
	}
	switch (enemystate)
	{
	case BOSS_ANI_IDLE:
	{
		enemy->GetAnimationsList()[BOSS_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case BOSS_ANI_WALKING:
	{
		enemy->GetAnimationsList()[BOSS_ANI_WALKING]->Render(spriteEnemyData);
	}
	break;
	}
}

