#pragma once
#include "GameItem.h"
class TimeFreeze :
	public GameItem
{
private:
	void LoadResources();
public:
	TimeFreeze();
	~TimeFreeze();
	static TimeFreeze * CreateTimeFreeze(int GameItemId ,float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


