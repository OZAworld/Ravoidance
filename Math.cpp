/*
Math.h
���w�I�ȏ���

15/05/23
Naoki Nakagawa
*/
#include "vtx.h"

namespace vtx
{
	//--------------------------------------------------
	// �v�Z�N���X
	//--------------------------------------------------

		// �R���X�g���N�^
	Math::Math()
	{

	}

		// �f�X�g���N�^
	Math::~Math()
	{

	}

		// �����̗���
	int Math::Random(int min, int max)
	{
		std::uniform_int_distribution<int> range(min, max);
		return range(mt);
	}

		// ���������̗���
	float Math::Random(float min, float max)
	{
		std::uniform_real_distribution<float> range(min, max);
		return range(mt);
	}
}
