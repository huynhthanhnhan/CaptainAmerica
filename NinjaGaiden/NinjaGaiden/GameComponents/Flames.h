#pragma once
#include "GameItem.h"
class Flames :
	public GameItem
{
private:
	void LoadResources();
public:
	Flames();
	~Flames();
	static Flames * CreateFlames(int GameItemId,float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};

