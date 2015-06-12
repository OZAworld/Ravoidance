/*
Math.h
���w�I�ȏ���

15/05/23
Naoki Nakagawa
*/
#pragma once

namespace vtx
{
	//--------------------------------------------------
	// �N���X
	//--------------------------------------------------

	// �v�Z�N���X
	class Math
	{
	private:

		// �����o�ϐ�
		std::mt19937 mt;

	public:

		// �R���X�g���N�^
		Math();

		// �f�X�g���N�^
		~Math();

		// �����̗���
		int Random(int min, int max);

		// ���������̗���
		float Random(float min, float max);

	};

}
