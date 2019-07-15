#include "GreenSoliderState.h"
#include "Grid.h"

GreenSoliderState::GreenSoliderState(GreenSolider * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

GreenSoliderState::~GreenSoliderState()
{
}

void GreenSoliderState::Jump()
{
}

void GreenSoliderState::Crouch()
{
}

void GreenSoliderState::JumpAttack()
{
}

void GreenSoliderState::Climb()
{
}

void GreenSoliderState::Idle()
{
}

void GreenSoliderState::Attack()
{
}

void GreenSoliderState::Walk()
{
}

void GreenSoliderState::Update(DWORD dt)
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

void GreenSoliderState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width = GREEN_SOLDIER_SPRITE_WIDTH;
		spriteEnemyData.height = GREEN_SOLDIER_SPRITE_HEIGHT;
		//spriteEnemyData.x = 200;
		spriteEnemyData.x = enemy->GetPositionX();
		//spriteEnemyData.y = 60;
		spriteEnemyData.y = enemy->GetPositionY();


		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();
	}
	switch (enemystate)
	{
	case  GREEN_SOLDIER_ANI_IDLE:
	{
		enemy->GetAnimationsList()[GREEN_SOLDIER_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case  GREEN_SOLDIER_ANI_WALKING:
	{
		enemy->GetAnimationsList()[GREEN_SOLDIER_ANI_WALKING]->Render(spriteEnemyData);

		/*enemy->Walk();*/
	}
	break;
	}
}

