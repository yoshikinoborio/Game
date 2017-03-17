#include "stdafx.h"
#include "BossEnemyHPBar.h"
#include "SceneManager.h"

//�{�X��HP�o�[�̑傫���B
namespace {
	const D3DXVECTOR2 HpBarMaxScale = { 10.0f,1.5f };
}

//�R���X�g���N�^�B
BossEnemyHPBar::BossEnemyHPBar()
{
	//�e�ϐ��̏������B
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//�f�X�g���N�^�B
BossEnemyHPBar::~BossEnemyHPBar()
{
}

//�������B
void BossEnemyHPBar::Initialize()
{
	m_position = D3DXVECTOR2(400.0f, 950.0f);
	m_angle = 0;
	m_scale = HpBarMaxScale;
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\hp.png";
	m_bossEnemy = &g_enemyManager->GetBoss();
	C2DImage::Initialize();
}

//�X�V�B
void BossEnemyHPBar::Update()
{
	//�{�X�G�l�~�[�̎c��HP�ɉ����Ăg�o�o�[�̃T�C�Y��ς���B
	float HpRate = (float)m_bossEnemy->GetHP() / (float)m_bossEnemy->GetMaxHP();
	m_scale = HpBarMaxScale;
	m_scale.x *= HpRate;
	C2DImage::SetScale(m_scale);
	this->SetupSlideMatrices();
}