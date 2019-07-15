#pragma once
#include "GameItem.h"

class Shuriken : public GameItem
{
	int damage = 10;

	vector<Animation *> animations;

	bool Active;

	float distance;
public:
	Shuriken();
	void CreateShuriken(float posx, float posy, float dt, bool isLeft);
	int GetDamage() { return this->damage; }
	bool IsActive() { return this->Active; }
	bool SetActive(bool value) { this->Active = value; }

	void LoadResources();

	void Update(DWORD dt) override;
	void Render() override;
	
	float GetDistance() { return this->distance; }

	~Shuriken();
};

