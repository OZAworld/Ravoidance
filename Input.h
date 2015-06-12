/*
Input.h
����

15/05/28
Naoki Nakagawa
*/
#pragma once

namespace vtx
{
	// ����`
	class Key;
	class Mouse;
	class Gamepad;

	//--------------------------------------------------
	// �N���X
	//--------------------------------------------------

	// �C���v�b�g�N���X
	class Input
	{
	private:

		LPDIRECTINPUT8 dInput;

	public:

		// �����o�ϐ�
		std::unique_ptr<Key> key;
		std::unique_ptr<Mouse> mouse;
		std::unique_ptr<Gamepad> gamepad;

		// �R���X�g���N�^
		Input(HWND hWnd);

		// �f�X�g���N�^
		~Input();

	};

	// �L�[�N���X
	class Key
	{
	private:

		// �����o�ϐ�
		LPDIRECTINPUTDEVICE8 dKey;
		BYTE state[256];
		BYTE old[256];

	public:

		// �R���X�g���N�^
		Key(LPDIRECTINPUT8 dInput, HWND hWnd);

		// �f�X�g���N�^
		~Key();

		// ��Ԃ̊Ď�
		void Check();

		// ��Ԃ��擾
		bool Get(int keyCode);

		// �L�[�A�b�v���擾
		bool GetUp(int keyCode);

		// �L�[�_�E�����擾
		bool GetDown(int keyCode);

	};

	// �}�E�X�N���X
	class Mouse
	{
	private:

		// �����o�ϐ�
		LPDIRECTINPUTDEVICE8 dMouse;
		DIMOUSESTATE2 state;
		DIMOUSESTATE2 old;
		POINT pos;

	public:

		// �R���X�g���N�^
		Mouse(LPDIRECTINPUT8 dInput, HWND hWnd);

		// �f�X�g���N�^
		~Mouse();

		// ��Ԃ̊Ď�
		void Check();

		// �{�^���̏�Ԃ��擾
		bool GetButton(int buttonCode);

		// �{�^���A�b�v���擾
		bool GetUpButton(int buttonCode);

		// �{�^���_�E�����擾
		bool GetDownButton(int buttonCode);

		// �}�E�X��X���W���擾
		int GetX();

		// �}�E�X��Y���W���擾
		int GetY();

	};


	// �Q�[���p�b�h�N���X
	class Gamepad
	{
	private:

		// �����o�ϐ�
		XINPUT_STATE state;
		XINPUT_STATE old;

	public:

		// �R���X�g���N�^
		Gamepad();

		// �f�X�g���N�^
		~Gamepad();

		// �Q�[���p�b�h���g���邩�̎擾
		bool Enable(int index);

		// ��Ԃ̊Ď�
		void Check();

		// �{�^���̏�Ԃ̎擾
		bool Get(int XINPUT_GAMEPAD_);

		// �{�^���𗣂������̎擾
		bool GetUp(int XINPUT_GAMEPAD_);

		// �{�^�������������̎擾
		bool GetDown(int XINPUT_GAMEPAD_);

		D3DXVECTOR2 LS();	// ���X�e�B�b�N
		D3DXVECTOR2 RS();	// �E�X�e�B�b�N
		float LT();			// ���g���K�[
		float RT();			// �E�g���K�[

	};
}
