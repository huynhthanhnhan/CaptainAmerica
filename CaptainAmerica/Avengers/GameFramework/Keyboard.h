#pragma once
#include "Game.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

#include "Global.h"
#include "../GameObject/Captain/Captain.h"

class CaptainState;

class Keyboard
{
	static Keyboard * __instance;
	HWND hWnd;		

	LPDIRECTINPUT8       di;	    
	LPDIRECTINPUTDEVICE8 didv;		

	BYTE  keyStates[256];			
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		

public:

	static Keyboard * GetInstance();

	//Khởi tạo bàn phím
	void InitKeyboard(HWND hWnd);
	void AuthorizeKeyboard();

	//Xử lí bàn phím
	virtual void ProcessKeyboard();

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	int IsKeyDown(int KeyCode);
	int IsKeyUp(int KeyCode);


	CaptainState *captainState;

	float countTimeJump = 0;
	float deltaDashLeft = 0;
	float deltaDashRight = 0;
	bool isCheckDashRight = false;
	bool isCheckDashLeft = false;
	float MaxTimeDash = 30;
	float deltaTimeDash = 0;

	void Update();

	~Keyboard();
};