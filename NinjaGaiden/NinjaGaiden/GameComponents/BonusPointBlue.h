#pragma once
#include "GameItem.h"
class BonusPointBlue :
	public GameItem
{
private:
	void LoadResources();
public:
	BonusPointBlue();
	~BonusPointBlue();
	static BonusPointBlue * CreateBonusPointBlue(int GameItemId ,float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


