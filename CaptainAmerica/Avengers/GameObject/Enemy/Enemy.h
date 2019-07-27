#pragma once
#include "../../GameFramework/GameObject.h"
#include "../../GameFramework/Global.h"

class Enemy : public GameObject
{
protected:
	eEnemyState eState;

	vector<Animation *> animation;

	EnemyType Type;
public:
	Enemy();
	void LoadResource();
	void SetState(eEnemyState state);

	eEnemyState GetEnumState() { return this->eState; }
	void SetEnumState(eEnemyState estate) { this->eState = estate; }

	vector<Animation *> GetAnimationList() { return this->animation; }

	bool isActive = false;

	void TurnLeft() { this->isLeft = true; }
	void TurnRight() { this->isLeft = false; }

	bool IsLeft() {return isLeft ? true : false; }

	virtual void Update(DWORD dt);
	virtual void Render();
};