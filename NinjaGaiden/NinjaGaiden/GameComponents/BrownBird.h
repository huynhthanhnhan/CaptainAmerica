#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Enemy.h"

class BrownBird :public Enemy
{
public:
	BrownBird();
	BrownBird(float posx , float posy);
	void LoadResources();
	void Idle();
	void Walk();
	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;
};
