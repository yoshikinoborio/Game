#pragma once
#include "2DImage.h"

//�{�X�̖��O�\���B
class BossEnemyName :public C2DImage
{
public:
	//�R���X�g���N�^�B
	BossEnemyName();

	//�f�X�g���N�^�B
	~BossEnemyName();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();
};

