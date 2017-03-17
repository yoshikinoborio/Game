#include "stdafx.h"
#include "BossEnemyHPBar.h"
#include "SceneManager.h"

//ボスのHPバーの大きさ。
namespace {
	const D3DXVECTOR2 HpBarMaxScale = { 10.0f,1.5f };
}

//コンストラクタ。
BossEnemyHPBar::BossEnemyHPBar()
{
	//各変数の初期化。
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//デストラクタ。
BossEnemyHPBar::~BossEnemyHPBar()
{
}

//初期化。
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

//更新。
void BossEnemyHPBar::Update()
{
	//ボスエネミーの残りHPに応じてＨＰバーのサイズを変える。
	float HpRate = (float)m_bossEnemy->GetHP() / (float)m_bossEnemy->GetMaxHP();
	m_scale = HpBarMaxScale;
	m_scale.x *= HpRate;
	C2DImage::SetScale(m_scale);
	this->SetupSlideMatrices();
}