#include "EnemyState.h"
#include "Grid.h"

EnemyState::EnemyState(Enemy * enemy, int enemystate)
{
}

EnemyState::~EnemyState()
{
}

void EnemyState::Jump()
{
}

void EnemyState::Crouch()
{
}

void EnemyState::JumpAttack()
{
}

void EnemyState::Climb()
{
}

void EnemyState::Idle()
{
}

void EnemyState::Attack()
{
}

void EnemyState::Walk()
{

}
void EnemyState::Update(DWORD dt)
{
	if (enemy->GetPositionY() < 35)
	{
		enemy->SetActive(false);
		enemy->SetStatus(true);
		return;
	}
}

void EnemyState::Render()
{
}
