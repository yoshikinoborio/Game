#pragma once
#include "2DImage.h"

//�v���C���[�����񂾎��ɏo�Ă���YOU DIED�N���X�B
class YOUDIED :public C2DImage
{
public:
	YOUDIED();
	~YOUDIED();
	void Initialize();
	void Update();
	//TRUE��n����YOU DIED�̃��l�𑝂₵�Ă����B
	void SetStartFlag(bool flag)
	{
		m_startFlag = flag;
	}
private:
	int m_alph;	//���l�̕ς��B
	bool m_startFlag; //TRUE�ɂȂ�����YOU DIED��������悤�ɂȂ�B
};