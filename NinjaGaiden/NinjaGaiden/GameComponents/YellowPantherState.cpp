#include "YellowPantherState.h"
#include "Grid.h"
#include "Constants.h"

YellowPantherState::YellowPantherState(YellowPanther * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

YellowPantherState::~YellowPantherState()
{
}

void YellowPantherState::Jump()
{
}

void YellowPantherState::Crouch()
{
}

void YellowPantherState::JumpAttack()
{
}

void YellowPantherState::Climb()
{
}

void YellowPantherState::Idle()
{
}

void YellowPantherState::Attack()
{
}

void YellowPantherState::Walk()
{
	switch (enemystate)
	{
	case YELLOW_PANTHER_ANI_WALKING:
	{
		enemy->SetSpeedX(YELLOW_PANTHER_WALKING_SPEED * (enemy->IsLeft() ? -1 : 1));
	}
	break;
	}
}

void YellowPantherState::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsEnemyInCamera(enemy) == true)
	{
		enemy->SetActive(true);
		enemy->SetSpeedX(YELLOW_PANTHER_WALKING_SPEED * (enemy->IsLeft() ? 1 : -1));

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

void YellowPantherState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width =  YELLOW_PANTHER_SPRITE_WIDTH;
		spriteEnemyData.height =  YELLOW_PANTHER_SPRITE_HEIGHT;
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
	case  YELLOW_PANTHER_ANI_IDLE:
	{
		enemy->GetAnimationsList()[ YELLOW_PANTHER_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case  YELLOW_PANTHER_ANI_WALKING:
	{
		enemy->GetAnimationsList()[ YELLOW_PANTHER_ANI_WALKING]->Render(spriteEnemyData);

		/*enemy->Walk();*/
	}
	break;
	}
}

