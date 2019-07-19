#pragma once
#include "GameObject.h"
#include "../../GameFramework/Constants.h"

class Brick : public GameObject
{
	ObjectType Type;
public:
	Brick();
	~Brick();

	ObjectType GetType() { return this->Type; }
	void SetType(ObjectType type) { this->Type = type; }
};

