#pragma once
#include "2DImage.h"
#include "UnityChan.h"

//�v���C���[��HP�o�[�N���X�B
class PlayerHPBar:public C2DImage
{
public:
	//�R���X�g���N�^�B
	PlayerHPBar();

	//�f�X�g���N�^�B
	~PlayerHPBar();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();
private:
	UnityChan*	m_unityChan;	//�v���C���[�̃C���X�^���X�B
};
