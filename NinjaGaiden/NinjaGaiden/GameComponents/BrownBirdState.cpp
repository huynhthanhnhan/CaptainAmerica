#include "BrownBirdState.h"
#include "Ninja.h"

BrownBirdState::BrownBirdState(BrownBird * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

BrownBirdState::~BrownBirdState()
{
}

void BrownBirdState::Jump()
{
}

void BrownBirdState::Crouch()
{
}

void BrownBirdState::JumpAttack()
{
}

void BrownBirdState::Climb()
{
}

void BrownBirdState::Idle()
{
}

void BrownBirdState::Attack()
{
}

void BrownBirdState::Walk()
{
}

void BrownBirdState::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsEnemyInCamera(enemy) == true)
	{
		enemy->SetActive(true);
		Ninja* ninja = Ninja::GetInstance();

		/*if (enemy->GetPositionX() < ninja->GetPositionX() - 50 &&
			enemy->GetPositionY() < ninja->GetPositionY() + 80)
		{
			enemy->SetSpeedX(BROWN_BIRD_SPEED/2);
			enemy->SetSpeedY(BROWN_BIRD_SPEED);
			enemy->TurnRight();

		}
		else if (enemy->GetPositionX() < ninja->GetPositionX() - 50 &&
			enemy->GetPositionY() > ninja->GetPositionY() + 80)
		{
			enemy->SetSpeedX(BROWN_BIRD_SPEED);
			enemy->SetSpeedY(-BROWN_BIRD_SPEED);
			enemy->TurnLeft();
		}
		else if (enemy->GetPositionX() >= ninja->GetPositionX() + 50 &&
			enemy->GetPositionY() > ninja->GetPositionY() + 80)
		{
			enemy->SetSpeedX(-BROWN_BIRD_SPEED);
			enemy->SetSpeedY(-BROWN_BIRD_SPEED);
			enemy->TurnRight();
		}
		else if (enemy->GetPositionX() >= ninja->GetPositionX() + 50 &&
			enemy->GetPositionY() < ninja->GetPositionY() + 80)
		{
			enemy->SetSpeedX(-BROWN_BIRD_SPEED/2);
			enemy->SetSpeedY(BROWN_BIRD_SPEED);
			enemy->TurnLeft();

		}*/
	}
	else
	{
		enemy->SetActive(false);
	}
}

void BrownBirdState::Render()
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

