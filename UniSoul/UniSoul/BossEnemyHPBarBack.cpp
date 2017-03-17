#include "stdafx.h"
#include "BossEnemyHPBarBack.h"

//コンストラクタ。
BossEnemyHPBarBack::BossEnemyHPBarBack()
{
}

//デストラクタ。
BossEnemyHPBarBack::~BossEnemyHPBarBack()
{
}

//初期化。
void BossEnemyHPBarBack::Initialize()
{
	m_position = D3DXVECTOR2(855.0f, 950.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.25f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\BossHpBack.png";
	C2DImage::Initialize();
}

//更新。
void BossEnemyHPBarBack::Update()
{
	this->SetupSlideMatrices();
}
