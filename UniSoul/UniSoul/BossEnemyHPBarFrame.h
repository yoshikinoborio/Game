#pragma once
#include "2DImage.h"

//�{�X�̗̑̓o�[�̃t���[���B
class BossEnemyHPBarFrame :public C2DImage
{
public:
	//�R���X�g���N�^�B
	BossEnemyHPBarFrame();

	//�f�X�g���N�^�B
	~BossEnemyHPBarFrame();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();
};

