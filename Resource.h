/*
Resource.h
���\�[�X

15/05/27
Naoki Nakagawa
*/
#pragma once

namespace vtx
{
	//--------------------------------------------------
	// �\����
	//--------------------------------------------------

	// �p�[�e�B�N���̍��W
	struct ParticleTransform
	{
		D3DXVECTOR3 pos;	// ���W
		D3DXVECTOR3 vec;	// �x�N�g��
		float gravity;		// �d�͉����x
		float size;			// �傫��
		int duration;		// ��������
	};

	//--------------------------------------------------
	// �N���X
	//--------------------------------------------------

	// ���b�V���N���X
	class Mesh
	{
	private:

		// �����o�ϐ�
		LPD3DXMESH mesh;
		LPD3DXBUFFER buffer;
		DWORD materialNum;

	public:

		// �R���X�g���N�^
		Mesh();

		// �R���X�g���N�^
		Mesh(const TCHAR *filePath);

		// �f�X�g���N�^
		~Mesh();

		// �ǂݍ���
		void Load(const TCHAR *filePath);

		// �`��
		void Draw(D3DXVECTOR3 *position, D3DXVECTOR3 *rotation, D3DXVECTOR3 *scale, LPDIRECT3DTEXTURE9 texture);

	};

	// �p�[�e�B�N��
	class Particle
	{
	private:

		LPDIRECT3DVERTEXBUFFER9	buffer;
		std::vector<ParticleTransform> transform;

	public:

		// �R���X�g���N�^
		Particle();

		// �f�X�g���N�^
		~Particle();

		// �p�[�e�B�N�����Z�b�g
		void Set(D3DXVECTOR3 pos,
			D3DXVECTOR3 vec,
			float gravity,
			float size,
			int duration);

		// �w�肵�����W�Ɍ������Đi��
		void Go(D3DXVECTOR3 pos, float power);

		// �`��
		void Draw(LPDIRECT3DTEXTURE9 texture);

	};

	// �e�N�X�`���N���X
	class Texture
	{
	private:

		// �����o�ϐ�
		LPDIRECT3DTEXTURE9 texture;

	public:

		// �R���X�g���N�^
		Texture();

		// �R���X�g���N�^
		Texture(const TCHAR *filePath);

		// �f�X�g���N�^
		~Texture();

		// �e�N�X�`���̓ǂݍ���
		void Load(const TCHAR *filePath);
		
		// �e�N�X�`���̎擾
		LPDIRECT3DTEXTURE9 Get();

	};

}
