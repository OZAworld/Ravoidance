/*
vtx.cpp
���C�u����

15/05/21
Naoki Nakagawa
*/
#include "vtx.h"

namespace vtx
{
	std::unique_ptr<App> app;
	std::unique_ptr<Render> render;
	std::unique_ptr<Input> input;
	std::unique_ptr<Math> math;

	//--------------------------------------------------
	// ���C�u�����N���X
	//--------------------------------------------------

	// �R���X�g���N�^
	Lib::Lib()
	{
		// ���������[�N���o���J�n����
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		app.reset(new App());
		render.reset(new Render(app->wnd->GetHandle(), app->wnd->GetFullScreen()));
		input.reset(new Input(app->wnd->GetHandle()));
		math.reset(new Math());
	}

	// �R���X�g���N�^
	Lib::Lib(TCHAR *title, int width, int height, bool isFullScreen)
	{
		// ���������[�N���o���J�n����
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		app.reset(new App(title, width, height, isFullScreen));
		render.reset(new Render(app->wnd->GetHandle(), isFullScreen));
		input.reset(new Input(app->wnd->GetHandle()));
		math.reset(new Math());
	}

	// �f�X�g���N�^
	Lib::~Lib()
	{
		// �f�o�b�O�r���h���ɏI���m�F�p�̃r�[�v����炷
#if defined(DEBUG) | defined(_DEBUG)
		MessageBeep(MB_OK);
#endif
		OutputDebugString(_T("���C�u������j�����܂����B\n"));
	}
}
