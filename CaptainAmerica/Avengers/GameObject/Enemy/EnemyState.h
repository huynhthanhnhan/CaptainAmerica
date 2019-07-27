#pragma once
#include "../../GameFramework/State.h"
#include "../../GameFramework/Global.h"
#include "Enemy.h"

class EnemyState : public State
{
private:
	Enemy * enemy;
	eEnemyState state;
public:
	EnemyState(Enemy * enemy, eEnemyState state);
	~EnemyState();
};