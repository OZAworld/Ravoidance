/*
App.cpp
�A�v���P�[�V����

15/05/21
Naoki Nakagawa
*/
#include "vtx.h"

namespace vtx
{
	//--------------------------------------------------
	// �A�v���P�[�V�����N���X
	//--------------------------------------------------

	// �R���X�g���N�^
	App::App()
		: wnd(new Window())
	{

	}

	// �R���X�g���N�^
	App::App(TCHAR *title, int width, int height, bool isFullScreen)
		: wnd(new Window(title, width, height, isFullScreen))
	{

	}

	// �f�X�g���N�^
	App::~App()
	{
		OutputDebugString(_T("�A�v���P�[�V������j�����܂����B\n"));
	}

	//--------------------------------------------------
	// �E�B���h�E�N���X
	//--------------------------------------------------

	// �R���X�g���N�^
	Window::Window()
	{
		Create(_T("vtx���C�u����"), 800, 600, false);
	}

	// �R���X�g���N�^
	Window::Window(TCHAR *title, int width, int height, bool isFullScreen)
	{
		Create(title, width, height, isFullScreen);
	}

	// �f�X�g���N�^
	Window::~Window()
	{
		OutputDebugString(_T("�E�B���h�E��j�����܂����B\n"));
	}

	// ���b�Z�[�W���[�v
	bool Window::MessageLoop()
	{
		MSG msg;

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				return false;
			}
		}

		input->key->Check();
		input->mouse->Check();
		input->gamepad->Check();

		return true;
	}

	// �n���h���̎擾
	const HWND Window::GetHandle()
	{
		return handle;
	}

	// �^�C�g���̎擾
	const TCHAR *Window::GetTitle()
	{
		return title;
	}

	// �E�B���h�E�̍��W�ƃT�C�Y�̎擾
	const RECT Window::GetRect()
	{
		return rect;
	}

	// �N���C�A���g�̈�̍��W�ƃT�C�Y�̎擾
	const RECT Window::GetRectClient()
	{
		RECT r = { 0 };
		GetClientRect(handle, &r);
		return r;
	}

	// �t���X�N���[���t���O�̎擾
	const bool Window::GetFullScreen()
	{
		return isFullScreen;
	}

	// �������ʏ���
	void Window::Create(TCHAR *title, int width, int height, bool isFullScreen)
	{
		// �����o�ϐ��̐ݒ�
		Window::title = title;
		rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
		Window::isFullScreen = isFullScreen;

		// �E�B���h�E�N���X�̐ݒ�
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.lpfnWndProc = Proc;
		wcex.hInstance = GetModuleHandle(nullptr);
		wcex.lpszClassName = (TCHAR *)Window::title;
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpszMenuName = (TCHAR *)Window::title;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

		// �E�B���h�E�N���X�̓o�^
		if (!RegisterClassEx(&wcex))
		{
			return;
		}

		// �E�B���h�E�̐���
		handle = CreateWindow(Window::title, Window::title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, wcex.hInstance, nullptr);

		if (!handle)
		{
			return;
		}

		// �E�B���h�E�̕\��
		ShowWindow(handle, SW_SHOWNORMAL);
		ValidateRect(handle, 0);
	}

	LRESULT CALLBACK Window::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_DESTROY)
		{
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
