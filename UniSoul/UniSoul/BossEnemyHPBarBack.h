#pragma once
#include "2DImage.h"

//�{�X�̗̑̓o�[�̔w�i�B
class BossEnemyHPBarBack : public C2DImage
{
public:
	//�R���X�g���N�^�B
	BossEnemyHPBarBack();

	//�f�X�g���N�^�B
	~BossEnemyHPBarBack();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();
};

