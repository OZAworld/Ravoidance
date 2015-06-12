/*
App.h
�A�v���P�[�V����

15/05/21
Naoki Nakagawa
*/
#pragma once

namespace vtx
{
	// ����`
	class Window;

	//--------------------------------------------------
	// �N���X
	//--------------------------------------------------

	// �A�v���P�[�V�����N���X
	class App
	{
	public:

		// �����o�ϐ�
		std::unique_ptr<Window> wnd;

		// �R���X�g���N�^
		App();

		// �R���X�g���N�^
		App(TCHAR *title, int width, int height, bool isFullScreen);

		// �f�X�g���N�^
		~App();

	};

	// �E�B���h�E�N���X
	class Window
	{
	private:

		// �����o�ϐ�
		HWND	handle;
		TCHAR	*title;
		RECT	rect;
		bool	isFullScreen;

	public:

		// �R���X�g���N�^
		Window();

		// �R���X�g���N�^
		Window(TCHAR *title, int width, int height, bool isFullScreen);

		// �f�X�g���N�^
		~Window();

		// ���b�Z�[�W���[�v
		bool MessageLoop();

		// �n���h���̎擾
		const HWND GetHandle();

		// �^�C�g���̎擾
		const TCHAR *GetTitle();

		// �E�B���h�E�̍��W�ƃT�C�Y�̎擾
		const RECT GetRect();

		// �N���C�A���g�̈�̍��W�ƃT�C�Y�̎擾
		const RECT GetRectClient();

		// �t���X�N���[���t���O�̎擾
		const bool GetFullScreen();

	private:

		// �������ʏ���
		void Create(TCHAR *title, int width, int height, bool isFullScreen);

		// �v���V�[�W��
		static LRESULT CALLBACK Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	};
}
