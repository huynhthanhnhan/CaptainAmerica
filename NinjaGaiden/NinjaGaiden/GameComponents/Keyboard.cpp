#include "Keyboard.h"
#include "Debug.h"

Keyboard * Keyboard::__instance = NULL;

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
		(HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE),
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

void Keyboard::Poll_Keyboard()
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
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}
}
// update trạng thái nhân vật khi nhấn nút
void Keyboard::UpdateKeyStates()
{
	Ninja * ninja = Ninja::GetInstance();

	if (ninja->IsClimbing() == false)
	{
		if (IsKeyDown(DIK_RIGHT))
		{
			if (!IsKeyDown(DIK_LEFT) && !ninja->IsAttacking() && ninja->IsGrounded() && !ninja->IsClimbing())
			{
				ninja->TurnRight();
				if (!IsKeyDown(DIK_DOWN))
				{
					ninja->Walk();
				}
				else
					ninja->Crouch();
			}
			else if (!IsKeyDown(DIK_DOWN))
				ninja->Idle();
		}
		else if (IsKeyDown(DIK_LEFT))
		{
			if (!IsKeyDown(DIK_RIGHT) && !ninja->IsAttacking() && ninja->IsGrounded() && !ninja->IsClimbing())
			{
				ninja->TurnLeft();
				if (IsKeyDown(DIK_DOWN))
				{
					ninja->Crouch();
					
				}
				else
					ninja->Walk();
			}
			else if (!IsKeyDown(DIK_DOWN))
				ninja->Idle();
		}
		else if (IsKeyDown(DIK_DOWN))
		{
			ninja->Crouch();
			if (IsKeyDown(DIK_S))
			{
				ninja->SetIsCrouching(true);
				ninja->Attack();
			}
		}
		else
		{
			ninja->Idle();
		}
	}
}
void Keyboard::OnKeyDown(int KeyCode)
{
	Ninja * ninja = Game::GetInstance()->GetNinja();
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
		case DIK_SPACE:
			ninja->Jump();
			ninja->SetIsClimbing(false);
			break;
		case DIK_S:
			if (true == ninja->IsGrounded() )
			{
				ninja->Attack();
			}
			else
			{
				ninja->JumpAttack();
			}
			break;
		case DIK_W:
			ninja->Climb();
			break;
		case DIK_D:
			ninja->CreateThrownWeapon();
			break;
		case DIK_UP:
			if (ninja->IsClimbing() == true)
			{
				ninja->SetPositionY(ninja->GetPositionY() + NINJA_CLIMB_SPEED * ninja->GetDt());
			}
			break;
	}
}
void Keyboard::OnKeyUp(int KeyCode)
{
	Ninja * ninja = Game::GetInstance()->GetNinja();
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
		case 0:
			break;
		case DIK_DOWN:
			ninja->SetIsCrouching(false);
		case DIK_S:
			//ninja->SetState(ninja->GetIdleState());
			break;
		case DIK_LEFT:
		case DIK_RIGHT:
			if (false == ninja->IsCrouching())
			{
				ninja->SetSpeedX(0);
				ninja->SetState(ninja->GetIdleState());
			}
			break;
		case DIK_D:
			ninja->SetState(ninja->GetIdleState());
			break;
	}
}

void Keyboard::Update()
{
	Poll_Keyboard();

	UpdateKeyStates();

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

//Hàm lấy đối tượng
Keyboard *Keyboard::GetInstance()
{
	if (__instance == NULL) __instance = new Keyboard();
	return __instance;
}
