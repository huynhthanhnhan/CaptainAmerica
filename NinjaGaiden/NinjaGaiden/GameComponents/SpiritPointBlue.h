#pragma once
#include "GameItem.h"
class SpiritPointBlue :
	public GameItem
{
private:
	void LoadResources();

	int HeathPoint = 5;

public:
	SpiritPointBlue();
	~SpiritPointBlue();
	static SpiritPointBlue * CreateSpiritPointBlue(int GameItemId,float posx, float posy, float dt);
	int GetHeathPoint() { return this->HeathPoint; }

	void Update(DWORD dt) override;
	void Render() override;
};

