#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "../GameObject/GameComponents/Sprite.h"
#include "Graphics.h"
using namespace std;

class Animation
{
	DWORD lastFrameTime;
	DWORD defaultDelayTime;

	vector< pair<Sprite *, DWORD> > frames;
	int curFrame;
public:
	Animation(DWORD defaultDelayTime) { this->defaultDelayTime = defaultDelayTime; };

	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }
	DWORD GetLastFrameTime() { return this->lastFrameTime; }	
	int GetCurFrame() { return curFrame; }
	void SetCurFrame(int f) { curFrame = f; }

	void Reset() { curFrame = -1; }
	void AddFrame(Sprite * sprite, DWORD time = 0);
	void Render(SpriteData spriteData);
};

