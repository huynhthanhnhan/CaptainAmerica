#pragma once
#include "../GameObject/GameComponents/Game.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

#include "Global.h"
class Keyboard
{
	static Keyboard * __instance;
	HWND hWnd;		

	LPDIRECTINPUT8       di;		//Đối tượng DirectInput8        
	LPDIRECTINPUTDEVICE8 didv;		//Đối tượng thiết bị của DirectInput8

	BYTE  keyStates[256];			//Bộ đệm trạng thái bàn phím
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		//Dữ liệu đệm bàn phím

public:

	static Keyboard * GetInstance();
	//Khởi tạo bàn phím
	void InitKeyboard(HWND hWnd);
	void AuthorizeKeyboard();

	//Xử lí bàn phím
	void ProcessKeyboard();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	float countTimeJump = 0;
	int count = 0;
	float deltaDashLeft = 0;
	float deltaDashRight = 0;
	bool isCheckDashRight = false;
	bool isCheckDashLeft = false;
	float MaxTimeDash = 40;
	float deltaTimeDash = 0;

	void Update();
	//Kiểm tra phím được nhấn
	int IsKeyDown(int KeyCode);
	int IsKeyUp(int KeyCode);

	//Hàm hủy đối tượng
	~Keyboard();
};