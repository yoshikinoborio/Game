#include "stdafx.h"
#include "Title.h"

//�R���X�g���N�^�B
Title::Title()
{
}

//�f�X�g���N�^�B
Title::~Title()
{
}

//�������B
void Title::Initialize()
{
	m_position = D3DXVECTOR2(680.0f, 380.0f);
	m_angle = 0;
	m_scale = Vector2One;
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\UniSoulTitle.png";
	C2DImage::Initialize();
}

//�X�V�B
void Title::Update()
{
	C2DImage::SetupMatrices();
}