#include "stdafx.h"
#include "BossEnemyName.h"

//コンストラクター
BossEnemyName::BossEnemyName()
{
	//各変数の初期化。
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//デストラクタ。
BossEnemyName::~BossEnemyName()
{
}

//初期化。
void BossEnemyName::Initialize()
{
	m_position = D3DXVECTOR2(250.0f, 950.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\BossName.png";
	C2DImage::Initialize();
}

//更新。
void BossEnemyName::Update()
{
	this->SetupMatrices();
}