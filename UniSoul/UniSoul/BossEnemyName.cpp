#include "stdafx.h"
#include "BossEnemyName.h"

//�R���X�g���N�^�[
BossEnemyName::BossEnemyName()
{
	//�e�ϐ��̏������B
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//�f�X�g���N�^�B
BossEnemyName::~BossEnemyName()
{
}

//�������B
void BossEnemyName::Initialize()
{
	m_position = D3DXVECTOR2(250.0f, 950.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\BossName.png";
	C2DImage::Initialize();
}

//�X�V�B
void BossEnemyName::Update()
{
	this->SetupMatrices();
}