#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "EnemyState.h"
#include "Enemy.h"

class BloodyBird :public Enemy
{
public:
	BloodyBird();
	BloodyBird(float posx, float posy);
	void LoadResources();
	void Idle();
	void Walk();
	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;
};

