#pragma once
#include "2DImage.h"

//�u���b�N�A�E�g�̕\���Ɏg���N���X�B
class Black :	public C2DImage
{
public:
	//�R���X�g���N�^�B
	Black();

	//�f�X�g���N�^�B
	~Black();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();

	//�����摜�̃��l�𑝂₵���茸�炵���肷��t���O�B
	void SetStartFlag(bool flag)
	{
		m_alphFlag = flag;
	}
private:
	int		m_alph;			//���l�̕ς��B
	bool	m_alphFlag;		//FALSE�̎��͂��񂾂�F�������Ȃ�TRUE�ɂ���ƔZ���Ȃ��Ă����B
};

