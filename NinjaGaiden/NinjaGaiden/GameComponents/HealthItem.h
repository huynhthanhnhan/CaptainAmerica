#pragma once
#include "GameItem.h"
class HealthItem :
	public GameItem
{
private:
	void LoadResources();

public:
	HealthItem();
	~HealthItem();
	static HealthItem * CreateHealthItem(int GameItemId,float posx, float posy, float dt);


	void Update(DWORD dt) override;
	void Render() override;
};


