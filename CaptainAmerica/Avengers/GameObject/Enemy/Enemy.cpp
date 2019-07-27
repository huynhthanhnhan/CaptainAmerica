#include "Enemy.h"
#include "../../GameFramework/Global.h"

Enemy::Enemy()
{
	LoadResource();
}
void Enemy::LoadResource()
{

}

void Enemy::SetState(eEnemyState state)
{
	this->eState = state;
}

//EnemyState * Enemy::GetIdleState()
//{
//	this->SetEnumState(eEnemyState::EnemyIDLE);
//	return idleState;
//}
//
//EnemyState * Enemy::GetWalkState()
//{
//	this->SetEnumState(eEnemyState::EnemyWALK);
//	return walkState;
//}
//
//EnemyState * Enemy::GetCrouchState()
//{
//	this->SetEnumState(eEnemyState::EnemyCROUCH);
//	return crouchState;
//}
//
//EnemyState * Enemy::GetHurtState()
//{
//	this->SetEnumState(eEnemyState::EnemyHURT);
//	return hurtState;
//}

void Enemy::Update(DWORD dt)
{

}
void Enemy::Render()
{

}