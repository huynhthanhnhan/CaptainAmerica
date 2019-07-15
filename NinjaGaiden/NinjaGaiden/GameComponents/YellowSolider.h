#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Enemy.h"

class YellowSolider :public Enemy
{
private:
public:
	YellowSolider();
	YellowSolider(float posx, float posy);
	void LoadResources();
	void Idle();
	void Walk();

	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render
	void Render() override;
};
