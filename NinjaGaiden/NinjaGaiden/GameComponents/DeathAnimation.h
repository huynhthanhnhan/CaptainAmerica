#pragma once
#include "GameObject.h"
#include "Enemy.h"

class Enemy;
class DeathAnimation :
	public GameObject
{
private :
	vector<Animation *> animations;

	void LoadResources();

	bool Active;
	EnemyType enemytype;

	int time, tempTime;
	bool checkTime;
public:
	DeathAnimation(EnemyType enemytype);
	~DeathAnimation();

	void SetEnemyType(EnemyType x) { this->enemytype = x; }
	EnemyType GetEnemyType() { return this->enemytype; }

	void SetTime(int x) { this->time = x; }

	bool CheckStatus() { return this->checkTime; }

	static DeathAnimation* CreateDeateAnimation(Enemy* gameobject);
	static DeathAnimation* CreateDeateAnimationForGameObject(GameObject* gameobject);
	static DeathAnimation * CreateDeateAnimation(Enemy * enemy, int posx, int posy);

	void Update(DWORD dt) override;
	void Render() override;

	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }
};

