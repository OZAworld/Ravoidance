/*
Input.h
入力

15/05/28
Naoki Nakagawa
*/
#pragma once

namespace vtx
{
	// 仮定義
	class Key;
	class Mouse;
	class Gamepad;

	//--------------------------------------------------
	// クラス
	//--------------------------------------------------

	// インプットクラス
	class Input
	{
	private:

		LPDIRECTINPUT8 dInput;

	public:

		// メンバ変数
		std::unique_ptr<Key> key;
		std::unique_ptr<Mouse> mouse;
		std::unique_ptr<Gamepad> gamepad;

		// コンストラクタ
		Input(HWND hWnd);

		// デストラクタ
		~Input();

	};

	// キークラス
	class Key
	{
	private:

		// メンバ変数
		LPDIRECTINPUTDEVICE8 dKey;
		BYTE state[256];
		BYTE old[256];

	public:

		// コンストラクタ
		Key(LPDIRECTINPUT8 dInput, HWND hWnd);

		// デストラクタ
		~Key();

		// 状態の監視
		void Check();

		// 状態を取得
		bool Get(int keyCode);

		// キーアップを取得
		bool GetUp(int keyCode);

		// キーダウンを取得
		bool GetDown(int keyCode);

	};

	// マウスクラス
	class Mouse
	{
	private:

		// メンバ変数
		LPDIRECTINPUTDEVICE8 dMouse;
		DIMOUSESTATE2 state;
		DIMOUSESTATE2 old;
		POINT pos;

	public:

		// コンストラクタ
		Mouse(LPDIRECTINPUT8 dInput, HWND hWnd);

		// デストラクタ
		~Mouse();

		// 状態の監視
		void Check();

		// ボタンの状態を取得
		bool GetButton(int buttonCode);

		// ボタンアップを取得
		bool GetUpButton(int buttonCode);

		// ボタンダウンを取得
		bool GetDownButton(int buttonCode);

		// マウスのX座標を取得
		int GetX();

		// マウスのY座標を取得
		int GetY();

	};


	// ゲームパッドクラス
	class Gamepad
	{
	private:

		// メンバ変数
		XINPUT_STATE state;
		XINPUT_STATE old;

	public:

		// コンストラクタ
		Gamepad();

		// デストラクタ
		~Gamepad();

		// ゲームパッドが使えるかの取得
		bool Enable(int index);

		// 状態の監視
		void Check();

		// ボタンの状態の取得
		bool Get(int XINPUT_GAMEPAD_);

		// ボタンを離したかの取得
		bool GetUp(int XINPUT_GAMEPAD_);

		// ボタンを押したかの取得
		bool GetDown(int XINPUT_GAMEPAD_);

		D3DXVECTOR2 LS();	// 左スティック
		D3DXVECTOR2 RS();	// 右スティック
		float LT();			// 左トリガー
		float RT();			// 右トリガー

	};
}
