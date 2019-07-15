#pragma once
#include "GameItem.h"
class WindmillStar :
	public GameItem
{
private:
	void LoadResources();
public:
	WindmillStar();
	~WindmillStar();
	static WindmillStar * CreateWindmillStar(int GameItemId, float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};

