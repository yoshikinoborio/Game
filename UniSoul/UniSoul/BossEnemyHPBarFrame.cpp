#include "stdafx.h"
#include "BossEnemyHPBarFrame.h"

//�R���X�g���N�^�B
BossEnemyHPBarFrame::BossEnemyHPBarFrame()
{
}

//�f�X�g���N�^�B
BossEnemyHPBarFrame::~BossEnemyHPBarFrame()
{
	//�e�ϐ��̏������B
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//�������B
void BossEnemyHPBarFrame::Initialize()
{
	m_position = D3DXVECTOR2(855.0f, 950.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.25f, 1.1f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\BossHpBarFrame.png";
	C2DImage::Initialize();
}

//�X�V�B
void BossEnemyHPBarFrame::Update()
{
	this->SetupSlideMatrices();
}
