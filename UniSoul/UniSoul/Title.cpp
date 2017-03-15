#include "stdafx.h"
#include "Title.h"

//コンストラクタ。
Title::Title()
{
}

//デストラクタ。
Title::~Title()
{
}

//初期化。
void Title::Initialize()
{
	m_position = D3DXVECTOR2(680.0f, 380.0f);
	m_angle = 0;
	m_scale = Vector2One;
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\UniSoulTitle.png";
	C2DImage::Initialize();
}

//更新。
void Title::Update()
{
	C2DImage::SetupMatrices();
}