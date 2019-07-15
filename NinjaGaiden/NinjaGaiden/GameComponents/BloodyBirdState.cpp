#include "BloodyBirdState.h"

BloodyBirdState::BloodyBirdState(BloodyBird * enemy, int enemystate)
{
	this->enemy = enemy;
	this->enemystate = enemystate;
}

BloodyBirdState::~BloodyBirdState()
{
}

void BloodyBirdState::Jump()
{
}

void BloodyBirdState::Crouch()
{
}

void BloodyBirdState::JumpAttack()
{
}

void BloodyBirdState::Climb()
{
}

void BloodyBirdState::Idle()
{
}

void BloodyBirdState::Attack()
{
}

void BloodyBirdState::Walk()
{
}

void BloodyBirdState::Update(DWORD dt)
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

void BloodyBirdState::Render()
{
	SpriteData spriteEnemyData;
	if (this->enemy != NULL)
	{
		spriteEnemyData.width = BLOODY_BIRD_SPRITE_WIDTH;
		spriteEnemyData.height = BLOODY_BIRD_SPRITE_HEIGHT;
		spriteEnemyData.x = enemy->GetPositionX();
		spriteEnemyData.y = enemy->GetPositionY();


		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();
	}
	switch (enemystate)
	{
	case BLOODY_BIRD_ANI_IDLE:
	{
		enemy->GetAnimationsList()[BLOODY_BIRD_ANI_IDLE]->Render(spriteEnemyData);
	}
	break;
	case BLOODY_BIRD_ANI_WALKING:
	{
		enemy->GetAnimationsList()[BLOODY_BIRD_ANI_WALKING]->Render(spriteEnemyData);
	}
	break;
	}
}

