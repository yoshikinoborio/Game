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

	//TRUE��n����YOU DIED�̃��l�𑝂₵�Ă����B
	void SetStartFlag(bool flag)
	{
		m_startFlag = flag;
	}
private:
	int		m_alph;		 //���l�̕ς��B
	bool	m_startFlag; //TRUE�ɂȂ�����YOU DIED��������悤�ɂȂ�B
};

