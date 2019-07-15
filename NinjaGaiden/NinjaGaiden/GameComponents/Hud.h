#pragma once
#include "GameObject.h"
#include "State.h"
#include "Constants.h"
#include "EnemyState.h"

class State;
class Hud :public GameObject
{

	static Hud * __instance;
	vector<Animation *> animations;
	int timecount;
	int count;
	int spirit_score;
public:
	Hud(float posx, float posy);

	static Hud * GetInstance();
	void LoadResources();

	//Hàm c?p nh?t
	void Update(DWORD dt) override;
	void Reset();
	//Hàm render
	void Render() override;
};


