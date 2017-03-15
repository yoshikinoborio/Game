#include "stdafx.h"
#include "PlayerHPBar.h"
#include "SceneManager.h"

//HPバーの大きさ。
const D3DXVECTOR2 HpBarMaxScale = { 3.0f,1.5f };

PlayerHPBar::PlayerHPBar()
{
	//各変数の初期化。
	m_position = D3DXVECTOR2(0.0f, 0.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(0.0f, 0.0f);
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}


PlayerHPBar::~PlayerHPBar()
{
}

void PlayerHPBar::Initialize()
{
	m_position = D3DXVECTOR2(170.0f,60.0f);
	m_angle = 0;
	m_scale = HpBarMaxScale;
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\hp.png";
	m_unityChan = g_pScenes->GetUnityChan();
	C2DImage::Initialize();
}

void PlayerHPBar::Update()
{
	////プレイヤーの残りHPに応じてＨＰバーのサイズを変える。
	float HpRate = (float)m_unityChan->GetHP() / (float)m_unityChan->GetMaxHP();
	m_scale = HpBarMaxScale;
	m_scale.x *= HpRate;
	C2DImage::SetScale(m_scale);
	this->SetupSlideMatrices();
}