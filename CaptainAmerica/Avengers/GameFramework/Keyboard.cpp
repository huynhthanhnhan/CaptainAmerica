#include "Keyboard.h"
#include "Debug.h"
Keyboard * Keyboard::__instance = NULL;

Keyboard *Keyboard::GetInstance()
{
	if (__instance == NULL) __instance = new Keyboard();
	return __instance;
}

int Keyboard::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}
int Keyboard::IsKeyUp(int KeyCode)
{
	return !(keyStates[KeyCode] & 0x80) > 0;
}
void Keyboard::InitKeyboard(HWND hWnd)
{
	//Khởi tạo DirectInput8
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);
	//Kiểm tra lỗi
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}
	//Khởi tạo device keyboard
	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	//Kiểm tra lỗi
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	//Chọn data format là bàn phím
	hr = didv->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] SetDataFormat failed!\n");
		return;
	}
	//Thiết lập mức độ hợp tác
	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] SetCooperativeLevel failed!\n");
		return;
	}

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size
	//Gọi hàm SetProperty để thiết lập chế độ đệm
	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);


	//Giành kiểm soát bàn phím
	hr = didv->Acquire();
	//Kiểm tra lỗi
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void Keyboard::AuthorizeKeyboard()
{
	//Lấy tất cả trạng thái của bàn phím
	HRESULT hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		//Nếu bàn phím mất focus hoặc chưa giành quyền kiểm soát được thì thử giành lại quyền kiểm soát
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			//Giành lại quyền kiểm soát
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDevicCaptainState failed. Error: %d\n", hr);
			return;
		}
	}
}
// update trạng thái nhân vật khi nhấn nút
void Keyboard::ProcessKeyboard()
{
	Captain * captain = Captain::GetInstance();
	captainState = new CaptainState(captain, IDLE);
	eController control = NoneControl;

	// Dash
	if (IsKeyDown(DIK_RIGHT) && !IsKeyDown(DIK_LEFT) && captain->IsGrounded() && !IsKeyDown(DIK_DOWN))
	{
		captain->TurnRight();
		if (deltaDashRight < 10 && deltaDashRight > 0)
		{
			isCheckDashRight = false;
			deltaTimeDash++;
			if (deltaTimeDash < MaxTimeDash)
			{
				captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * 2 * (captain->IsLeft() ? -1 : 1));
				captain->SetState(DASH);
				return;
			}
			else
			{
				captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
				captain->SetState(WALK);
				return;
			}
		}
		else
		{
			deltaTimeDash = 0;
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			captain->SetState(WALK);
			return;
		}
	}

	if (IsKeyDown(DIK_LEFT) && !IsKeyDown(DIK_RIGHT) && captain->IsGrounded() && !IsKeyDown(DIK_DOWN))
	{
		captain->TurnLeft();
		if (deltaDashLeft < 10 && deltaDashLeft > 0)
		{
			isCheckDashLeft = false;
			deltaTimeDash++;
			if (deltaTimeDash < MaxTimeDash)
			{
				captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * 2 * (captain->IsLeft() ? -1 : 1));
				captain->SetState(DASH);
				return;
			}
			else
			{
				captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
				captain->SetState(WALK);
				return;
			}
		}
		else
		{
			deltaTimeDash = 0;
			captain->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X * (captain->IsLeft() ? -1 : 1));
			captain->SetState(WALK);
			return;
		}
	}
	//if (IsKeyDown(DIK_RIGHT))
	//{
	//	if (!IsKeyDown(DIK_LEFT) && captain->IsGrounded())
	//	{
	//		
	//		if (IsKeyDown(DIK_DOWN))
	//		{
	//			captain->Crouch();
	//		}
	//		else

	//	}
	//	else if (!IsKeyDown(DIK_LEFT) && captain->isWading)
	//	{
	//		captain->TurnRight();
	//		if (!IsKeyDown(DIK_DOWN))
	//			captain->SetSpeedX(CAPTAIN_AMERICA_WADING_SPEED * (captain->IsLeft() ? -1 : 1));
	//	}
	//	else if (!IsKeyDown(DIK_DOWN))
	//		captain->Idle();
	//}
	//else if (IsKeyDown(DIK_LEFT))
	//{
	//	if (!IsKeyDown(DIK_RIGHT) && captain->IsGrounded())
	//	{
	//		captain->TurnLeft();
	//		if (IsKeyDown(DIK_DOWN))
	//		{
	//			captain->Crouch();

	//		}
	//		else
	//			if (deltaDashLeft < 10 && deltaDashLeft > 0) 
	//			{
	//				isCheckDashLeft = false;
	//				deltaTimeDash ++;
	//				if (deltaTimeDash < MaxTimeDash)
	//				{
	//					captain->Dash();
	//				}
	//				else
	//				{
	//					captain->Walk();
	//				}
	//			}
	//			else
	//			{
	//				deltaTimeDash = 0;
	//				captain->Walk();
	//			}
	//	}
	//	else if (!IsKeyDown(DIK_RIGHT) && captain->isWading)
	//	{
	//		captain->TurnLeft();
	//		if (!IsKeyDown(DIK_DOWN))
	//			captain->SetSpeedX(CAPTAIN_AMERICA_WADING_SPEED * (captain->IsLeft() ? -1 : 1));
	//	}
	//	else if (!IsKeyDown(DIK_DOWN))
	//		captain->Idle();
	//}
	//else if (IsKeyDown(DIK_DOWN))
	//{
	//	if (!IsKeyDown(DIK_F))
	//		if (IsKeyDown(DIK_SPACE) && count == 0)
	//		{
	//			captain->SetPositionY(captain->GetPositionY() - 0.5);
	//			count = 1;
	//		}
	//		else
	//		captain->Crouch();
	//	else  
	//		//if (count == 0) 
	//		{
	//			captain->CrouchHit();
	//			//count = 1;
	//		}
	//		
	//}
	//else if (IsKeyDown(DIK_UP))
	//{
	//	captain->ShieldUp();
	//}
	//else
	//{
	//	if(!captain->isThrowing )
	//		captain->Idle();
	//}
	//if(IsKeyDown(DIK_F)&&!captain->isWading)
	//{
	//	if (!captain->isThrowing)
	//	{
	//		if (captain->IsGrounded())
	//		{
	//			captain->ThrowShield();
	//		}
	//		else
	//		{
	//			captain->Kick();
	//		}
	//		
	//	}
	//}


	if (IsKeyDown(DIK_RIGHT) && !IsKeyDown(DIK_LEFT))
	{
		captain->TurnRight();
		control = RightControl;
	}

	if (IsKeyDown(DIK_LEFT) && !IsKeyDown(DIK_RIGHT))
	{
		captain->TurnLeft();
		control = LeftControl;
	}

	if (IsKeyDown(DIK_UP))
	{
		control = UpControl;
	}

	if (IsKeyDown(DIK_DOWN))
	{
		control = DownControl;
	}

	if (IsKeyDown(DIK_F))
	{
		control = ThrowControl;
	}

	if (IsKeyDown(DIK_SPACE))
	{
		control = JumpControl;
	}

	captainState->SetNewState(captain->GetEnumState(), control);


}
void Keyboard::OnKeyDown(int KeyCode)
{
}
void Keyboard::OnKeyUp(int KeyCode)
{
	Captain* captain = Game::GetInstance()->GetCaptain();
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		captain->SetIsCrouching(false);
	case DIK_LEFT:
		//if (!isCheckDashLeft)
	{
		deltaDashLeft = 0;
		isCheckDashLeft = true;
	}

	break;
	case DIK_RIGHT:
		//if (!isCheckDashRight)
	{
		deltaDashRight = 0;
		isCheckDashRight = true;
	}

	break;
	}
}

void Keyboard::Update()
{
	//countTimeJump+
	if (isCheckDashLeft)
		deltaDashLeft++;
	if (deltaDashLeft > 10)
		isCheckDashLeft = false;
	if (isCheckDashRight)
		deltaDashRight++;
	if (deltaDashRight > 10)
		isCheckDashRight = false;

	AuthorizeKeyboard();

	ProcessKeyboard();

	//Lấy các sự kiện bàn phím được đệm
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	//Kiểm tra lỗi
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	//Kiểm tra các phím được đệm, xem phím nào được nhấn xuống hoặc thả ra, rồi xử lí
	for (DWORD i = 0; i < dwElements; i++)
	{
		//Lấy keycode được nhấn
		int KeyCode = keyEvents[i].dwOfs;
		//Lấy trạng thái của phím đang xét
		int KeyState = keyEvents[i].dwData;
		//Kiểm tra xem phím được nhấn hay được thả ra
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}
//Hàm hủy Keyboard chính
Keyboard::~Keyboard()
{
	if (didv != NULL)
	{
		didv->Unacquire();
		didv->Release();
	}
	if (di != NULL) di->Release();
}

