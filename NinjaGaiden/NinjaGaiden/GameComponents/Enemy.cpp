#include "Enemy.h"
#include "Constants.h"
#include "Grid.h"

Enemy::Enemy()
{
	SetActive(false);
	LoadResources();
}
void Enemy::LoadResources()
{
}

void Enemy::SetState(EnemyState * state)
{
	this->state = state;
}
EnemyState * Enemy::GetIdleState()
{
	return idleState;
}
EnemyState * Enemy::GetWalkingState()
{
	return walkingState;
}
void Enemy::SetItemType(int itemtype)
{
	switch (itemtype)
	{
	case 1:
		this->itemtype = Item::FLAMES;
		break;
	case 2:
		this->itemtype = Item::SHURIKEN;
		break;
	case 3:
		this->itemtype = Item::WINDMILLSTAR;
		break;
	case 4:
		this->itemtype = Item::FIREWHEELS;
	break;	
	case 5:
		this->itemtype = Item::SPIRITPOINTBLUE;
		break;
	case 6:
		this->itemtype = Item::SPIRITPOINTRED;
		break;
	case 7:
		this->itemtype = Item::TIMEFREEZE;
		break;
	case 8:
		this->itemtype = Item::THROWINGSTAR;
		break;
	case 9:
		this->itemtype = Item::BONUSPOINTBLUE;
		break;
	case 10:
		this->itemtype = Item::BONUSPOINTRED;
		break;
	case 11:
		this->itemtype = Item::HEALTHITEM;
		break;
	default:
		break;
	}
}
void Enemy::SetBoudary(int min_posx, int max_posx)
{
	this->min_posx = min_posx;
	this->max_posx = max_posx;
}
void Enemy::Idle()
{
}

void Enemy::Walk()
{
}

void Enemy::TurnLeft()
{
	isLeft = true;
}
void Enemy::TurnRight()
{
	isLeft = false;
}
void Enemy::ResetCollider()
{
	this->collider.width = 0;
	this->collider.height = 0;
	this->collider.x = 0;
	this->collider.y = 0;
	this->collider.vx = 0;
	this->collider.vy = 0;
}
void Enemy::TakeDamage(int damage)
{
	this->stamina -= damage;
}
void Enemy::Update(DWORD dt)
{
	state->Update(dt);
	if (this->GetPositionX() <= 0)
	{
		int EnemyPosInGrid = Grid::GetInstance()->GetEnemyIndexById(this->Id);
		Grid::GetInstance()->DeleteEnemy(EnemyPosInGrid);
	}
}
void Enemy::Render()
{
}