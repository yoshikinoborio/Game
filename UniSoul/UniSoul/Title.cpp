#include "stdafx.h"
#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	m_position = D3DXVECTOR2(680.0f, 380.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\UniSoulTitle.png";
	C2DImage::Initialize();
}

void Title::Update()
{
	C2DImage::SetupMatrices();
}