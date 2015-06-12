/*
Render.h
�`�揈��

15/05/21
Naoki Nakagawa
*/
#pragma once

namespace vtx
{

	//--------------------------------------------------
	// �N���X
	//--------------------------------------------------

	// �`��N���X
	class Render
	{
	private:

		// �����o�ϐ�
		LPDIRECT3D9			direct3d;
		LPDIRECT3DDEVICE9	d3d;		//�`��f�o�C�X

	public:

		// �R���X�g���N�^
		Render(HWND hWnd, bool isFullScreen);

		// �f�X�g���N�^
		~Render();

		// �`��̊J�n
		void Start();

		// �`��̏I��
		void End();

		// ��ʂ̃N���A
		void Clear(DWORD color);

		// 3D�f�o�C�X�̎擾
		const LPDIRECT3DDEVICE9 GetD3d();

	};

	// �J�����N���X
	class Camera
	{
	private:

		// �����o�ϐ�
		float aspect;
		D3DXMATRIX m_view;
		D3DXMATRIX m_projection;

	public:

		// �����o�ϐ�
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rota;

		// �R���X�g���N�^
		Camera();

		// �R���X�g���N�^
		Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rota);

		// �f�X�g���N�^
		~Camera();

		// �������ʏ���
		void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rota);

		// �B�e
		void View();

		// �r���[�|�[�g�̐ݒ�
		void SetViewPort(int x, int y, int width, int height);

	};

}
