/*
Input.cpp
入力

15/05/28
Naoki Nakagawa
*/
#include "vtx.h"
#define SafeRelease(p) if (p) { p->Release(); p = nullptr; }

namespace vtx
{
	//--------------------------------------------------
	// インプットクラス
	//--------------------------------------------------

	// コンストラクタ
	Input::Input(HWND hWnd)
	{
		if (FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dInput, nullptr)))
		{
			return;
		}

		mouse.reset(new Mouse(dInput, hWnd));
		key.reset(new Key(dInput, hWnd));
		gamepad.reset(new Gamepad());
	}

	// デストラクタ
	Input::~Input()
	{
		SafeRelease(dInput);
	}

	//--------------------------------------------------
	// キークラス
	//--------------------------------------------------

		// コンストラクタ
	Key::Key(LPDIRECTINPUT8 dInput, HWND hWnd)
	{
		if (FAILED(dInput->CreateDevice(GUID_SysKeyboard, &dKey, nullptr)))
		{
			return;
		}

		if (FAILED(dKey->SetDataFormat(&c_dfDIKeyboard)))
		{
			return;
		}

		if (FAILED(dKey->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		{
			return;
		}
	}

		// デストラクタ
	Key::~Key()
	{
		dKey->Unacquire();
		SafeRelease(dKey);
	}

	// 状態の監視
	void Key::Check()
	{
		std::memcpy(old, state, sizeof(state));
		dKey->GetDeviceState(256, state);

		dKey->Acquire();
	}

	// 状態を取得
	bool Key::Get(int keyCode)
	{
		return state[keyCode] & 0xf0;
	}

	// キーアップを取得
	bool Key::GetUp(int keyCode)
	{
		if (!(state[keyCode] & 0xf0)
			&& (old[keyCode] & 0xf0))
		{
			return true;
		}

		return false;
	}

	// キーダウンを取得
	bool Key::GetDown(int keyCode)
	{
		if ((state[keyCode] & 0xf0)
			&& !(old[keyCode] & 0xf0))
		{
  			return true;
		}

		return false;
	}

	//--------------------------------------------------
	// マウスクラス
	//--------------------------------------------------

	// コンストラクタ
	Mouse::Mouse(LPDIRECTINPUT8 dInput, HWND hWnd)
	{
		if (FAILED(dInput->CreateDevice(GUID_SysMouse, &dMouse, nullptr)))
		{
			return;
		}

		if (FAILED(dMouse->SetDataFormat(&c_dfDIMouse2)))
		{
			return;
		}

		if (FAILED(dMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		{
			return;
		}

		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_ABS;

		if (FAILED(dMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
		{
			return;
		}
	}

	// デストラクタ
	Mouse::~Mouse()
	{
		dMouse->Unacquire();
		SafeRelease(dMouse);
	}

	// 状態の監視
	void Mouse::Check()
	{
		// マウスのボタンの状態の取得
		old = state;
		dMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &state);

		// マウスの座標の取得
		RECT wndRect;
		GetCursorPos(&pos);
		GetWindowRect(app->wnd->GetHandle(), &wndRect);
		pos.x -= wndRect.left;
		pos.y -= wndRect.top;

		dMouse->Acquire();
	}

	// マウスのボタンの状態を取得
	bool Mouse::GetButton(int buttonCode)
	{
		if (state.rgbButtons[buttonCode])
		{
			return true;
		}

		return false;
	}

	// ボタンアップを取得
	bool Mouse::GetUpButton(int buttonCode)
	{
		if (!state.rgbButtons[buttonCode]
			&& old.rgbButtons[buttonCode])
		{
			return true;
		}

		return false;
	}

	// ボタンダウンを取得
	bool Mouse::GetDownButton(int buttonCode)
	{
		if (state.rgbButtons[buttonCode]
			&& !old.rgbButtons[buttonCode])
		{
			return true;
		}

		return false;
	}

	// マウスの座標を取得
	int Mouse::GetX()
	{
		return pos.x;
	}

	// マウスの座標を取得
	int Mouse::GetY()
	{
		return pos.y;
	}

	//--------------------------------------------------
	// ゲームパッドクラス
	//--------------------------------------------------

	// コンストラクタ
	Gamepad::Gamepad()
	{

	}

	// デストラクタ
	Gamepad::~Gamepad()
	{

	}

	// ゲームパッドが使えるかの取得
	bool Gamepad::Enable(int index)
	{
		if (XInputGetState(index - 1, &state) == ERROR_SUCCESS)
		{
			return true;
		}

		return false;
	}

	// 状態の監視
	void Gamepad::Check()
	{
		old = state;
		XInputGetState(0, &state);
	}

	// ボタンの状態の取得
	bool Gamepad::Get(int XINPUT_GAMEPAD_)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_)
		{
			return true;
		}

		return false;
	}

	// ボタンを離したかの取得
	bool Gamepad::GetUp(int XINPUT_GAMEPAD_)
	{
		if (!(state.Gamepad.wButtons & XINPUT_GAMEPAD_)
			&& (state.Gamepad.wButtons & XINPUT_GAMEPAD_))
		{
			return true;
		}

		return false;
	}

	// ボタンを押したかの取得
	bool Gamepad::GetDown(int XINPUT_GAMEPAD_)
	{
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_)
			&& !(state.Gamepad.wButtons & XINPUT_GAMEPAD_))
		{
			return true;
		}

		return false;
	}

	// 左スティック
	D3DXVECTOR2 Gamepad::LS()
	{
		D3DXVECTOR2 analogValue(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
		if (analogValue.x > 0)analogValue.x++;
		if (analogValue.y > 0)analogValue.y++;
		analogValue /= 32768.0f;
		return analogValue;
	}

	// 右スティック
	D3DXVECTOR2 Gamepad::RS()
	{
		D3DXVECTOR2 analogValue(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
		if (analogValue.x > 0)analogValue.x++;
		if (analogValue.y > 0)analogValue.y++;
		analogValue /= 32768.0f;
		return analogValue;
	}

	// 左トリガー
	float Gamepad::LT()
	{
		float analogValue = state.Gamepad.bLeftTrigger / 255.0f;
		return analogValue;
	}

	// 右トリガー
	float Gamepad::RT()
	{
		float analogValue = state.Gamepad.bRightTrigger / 255.0f;
		return analogValue;
	}
}
