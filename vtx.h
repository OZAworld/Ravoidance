/*
vtx.h
���C�u�����̃w�b�_�t�@�C��

15/05/21
Naoki Nakagawa
*/
#pragma once

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "dxguid.lib")

// C++�n
#include <vector>
#include <memory>
#include <random>
// Windows�n
#include <Windows.h>
#include <tchar.h>
// DirectX�n
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <XInput.h>
// vtx���C�u�����n
#include "App.h"
#include "Render.h"
#include "Resource.h"
#include "Input.h"
#include "Math.h"

//#define Main() WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPravInstance, LPSTR lpCmdLine, int nCmdShow)

namespace vtx
{
	extern std::unique_ptr<App> app;
	extern std::unique_ptr<Render> render;
	extern std::unique_ptr<Input> input;
	extern std::unique_ptr<Math> math;
	
	//--------------------------------------------------
	// �N���X
	//--------------------------------------------------

	// ���C�u�����N���X
	class Lib
	{
	public:

		// �R���X�g���N�^
		Lib();

		// �R���X�g���N�^
		Lib(TCHAR *title, int width, int height, bool isFullScreen);

		// �f�X�g���N�^
		~Lib();

	};
}
