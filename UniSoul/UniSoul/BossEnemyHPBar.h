#pragma once
#include "2DImage.h"
#include "EnemyBoss.h"

//�{�X�̗̑̓o�[�B
class BossEnemyHPBar :public C2DImage
{
public:
	//�R���X�g���N�^�B
	BossEnemyHPBar();

	//�f�X�g���N�^�B
	~BossEnemyHPBar();
	//�������B
	void Initialize();

	//�X�V�B
	void Update();
private:
	EnemyBoss*	m_bossEnemy;	//�{�X�̃C���X�^���X�B
};

