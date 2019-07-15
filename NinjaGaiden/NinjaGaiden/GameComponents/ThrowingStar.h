#pragma once
#include "GameItem.h"
class ThrowingStar :
	public GameItem
{
private:
	void LoadResources();
public:
	ThrowingStar();
	~ThrowingStar();
	static ThrowingStar * CreateThrowingStar(int GameItemId ,float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


