#pragma once
#include "2DImage.h"

//�v���C���[�����񂾎��ɏo�Ă���You Died�N���X�B
class YouDied :public C2DImage
{
public:
	//�R���X�g���N�^�B
	YouDied();

	//�f�X�g���N�^�B
	~YouDied();
	//�������B
	void Initialize();

	//�X�V�B
	void Update();

private:
	int		m_alph;		 //���l�̕ς��B
};

