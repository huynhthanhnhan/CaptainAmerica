#include "EnemyState.h"

EnemyState::EnemyState(Enemy * enemy, eEnemyState state)
{
	this->enemy = enemy;
	this->state = state;
}
EnemyState::~EnemyState()
{

}
