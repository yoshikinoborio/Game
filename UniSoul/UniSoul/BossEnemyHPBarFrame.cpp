#include "stdafx.h"
#include "BossEnemyHPBarFrame.h"

//コンストラクタ。
BossEnemyHPBarFrame::BossEnemyHPBarFrame()
{
}

//デストラクタ。
BossEnemyHPBarFrame::~BossEnemyHPBarFrame()
{
	//各変数の初期化。
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//初期化。
void BossEnemyHPBarFrame::Initialize()
{
	m_position = D3DXVECTOR2(855.0f, 950.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.25f, 1.1f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\BossHpBarFrame.png";
	C2DImage::Initialize();
}

//更新。
void BossEnemyHPBarFrame::Update()
{
	this->SetupSlideMatrices();
}
