/*
Input.cpp
����

15/05/28
Naoki Nakagawa
*/
#include "vtx.h"
#define SafeRelease(p) if (p) { p->Release(); p = nullptr; }

namespace vtx
{
	//--------------------------------------------------
	// �C���v�b�g�N���X
	//--------------------------------------------------

	// �R���X�g���N�^
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

	// �f�X�g���N�^
	Input::~Input()
	{
		SafeRelease(dInput);
	}

	//--------------------------------------------------
	// �L�[�N���X
	//--------------------------------------------------

		// �R���X�g���N�^
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

		// �f�X�g���N�^
	Key::~Key()
	{
		dKey->Unacquire();
		SafeRelease(dKey);
	}

	// ��Ԃ̊Ď�
	void Key::Check()
	{
		std::memcpy(old, state, sizeof(state));
		dKey->GetDeviceState(256, state);

		dKey->Acquire();
	}

	// ��Ԃ��擾
	bool Key::Get(int keyCode)
	{
		return state[keyCode] & 0xf0;
	}

	// �L�[�A�b�v���擾
	bool Key::GetUp(int keyCode)
	{
		if (!(state[keyCode] & 0xf0)
			&& (old[keyCode] & 0xf0))
		{
			return true;
		}

		return false;
	}

	// �L�[�_�E�����擾
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
	// �}�E�X�N���X
	//--------------------------------------------------

	// �R���X�g���N�^
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

	// �f�X�g���N�^
	Mouse::~Mouse()
	{
		dMouse->Unacquire();
		SafeRelease(dMouse);
	}

	// ��Ԃ̊Ď�
	void Mouse::Check()
	{
		// �}�E�X�̃{�^���̏�Ԃ̎擾
		old = state;
		dMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &state);

		// �}�E�X�̍��W�̎擾
		RECT wndRect;
		GetCursorPos(&pos);
		GetWindowRect(app->wnd->GetHandle(), &wndRect);
		pos.x -= wndRect.left;
		pos.y -= wndRect.top;

		dMouse->Acquire();
	}

	// �}�E�X�̃{�^���̏�Ԃ��擾
	bool Mouse::GetButton(int buttonCode)
	{
		if (state.rgbButtons[buttonCode])
		{
			return true;
		}

		return false;
	}

	// �{�^���A�b�v���擾
	bool Mouse::GetUpButton(int buttonCode)
	{
		if (!state.rgbButtons[buttonCode]
			&& old.rgbButtons[buttonCode])
		{
			return true;
		}

		return false;
	}

	// �{�^���_�E�����擾
	bool Mouse::GetDownButton(int buttonCode)
	{
		if (state.rgbButtons[buttonCode]
			&& !old.rgbButtons[buttonCode])
		{
			return true;
		}

		return false;
	}

	// �}�E�X�̍��W���擾
	int Mouse::GetX()
	{
		return pos.x;
	}

	// �}�E�X�̍��W���擾
	int Mouse::GetY()
	{
		return pos.y;
	}

	//--------------------------------------------------
	// �Q�[���p�b�h�N���X
	//--------------------------------------------------

	// �R���X�g���N�^
	Gamepad::Gamepad()
	{

	}

	// �f�X�g���N�^
	Gamepad::~Gamepad()
	{

	}

	// �Q�[���p�b�h���g���邩�̎擾
	bool Gamepad::Enable(int index)
	{
		if (XInputGetState(index - 1, &state) == ERROR_SUCCESS)
		{
			return true;
		}

		return false;
	}

	// ��Ԃ̊Ď�
	void Gamepad::Check()
	{
		old = state;
		XInputGetState(0, &state);
	}

	// �{�^���̏�Ԃ̎擾
	bool Gamepad::Get(int XINPUT_GAMEPAD_)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_)
		{
			return true;
		}

		return false;
	}

	// �{�^���𗣂������̎擾
	bool Gamepad::GetUp(int XINPUT_GAMEPAD_)
	{
		if (!(state.Gamepad.wButtons & XINPUT_GAMEPAD_)
			&& (state.Gamepad.wButtons & XINPUT_GAMEPAD_))
		{
			return true;
		}

		return false;
	}

	// �{�^�������������̎擾
	bool Gamepad::GetDown(int XINPUT_GAMEPAD_)
	{
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_)
			&& !(state.Gamepad.wButtons & XINPUT_GAMEPAD_))
		{
			return true;
		}

		return false;
	}

	// ���X�e�B�b�N
	D3DXVECTOR2 Gamepad::LS()
	{
		D3DXVECTOR2 analogValue(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
		if (analogValue.x > 0)analogValue.x++;
		if (analogValue.y > 0)analogValue.y++;
		analogValue /= 32768.0f;
		return analogValue;
	}

	// �E�X�e�B�b�N
	D3DXVECTOR2 Gamepad::RS()
	{
		D3DXVECTOR2 analogValue(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
		if (analogValue.x > 0)analogValue.x++;
		if (analogValue.y > 0)analogValue.y++;
		analogValue /= 32768.0f;
		return analogValue;
	}

	// ���g���K�[
	float Gamepad::LT()
	{
		float analogValue = state.Gamepad.bLeftTrigger / 255.0f;
		return analogValue;
	}

	// �E�g���K�[
	float Gamepad::RT()
	{
		float analogValue = state.Gamepad.bRightTrigger / 255.0f;
		return analogValue;
	}
}
