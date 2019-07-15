#include "RedBirdState.h"

RedBirdState::RedBirdState(RedBird * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

RedBirdState::~RedBirdState()
{
}

void RedBirdState::Jump()
{
}

void RedBirdState::Crouch()
{
}

void RedBirdState::JumpAttack()
{
}

void RedBirdState::Climb()
{
}

void RedBirdState::Idle()
{
}

void RedBirdState::Attack()
{
}

void RedBirdState::Walk()
{
}

void RedBirdState::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsEnemyInCamera(enemy) == true)
	{
		enemy->SetActive(true);
	}
	else
	{
		enemy->SetActive(false);
	}
}

void RedBirdState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width = BROWN_BIRD_SPRITE_WIDTH;
		spriteEnemyData.height = BROWN_BIRD_SPRITE_HEIGHT;
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
	case BROWN_BIRD_ANI_IDLE:
	{
		enemy->GetAnimationsList()[BROWN_BIRD_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case BROWN_BIRD_ANI_WALKING:
	{
		enemy->GetAnimationsList()[BROWN_BIRD_ANI_WALKING]->Render(spriteEnemyData);

		/*enemy->Walk();*/
	}
	break;
	}
}

