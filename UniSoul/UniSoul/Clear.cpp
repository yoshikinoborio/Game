#include "stdafx.h"
#include "Clear.h"


Clear::Clear()
{
}


Clear::~Clear()
{
}

void Clear::Initialize()
{
	m_position = D3DXVECTOR2(682.0f, 300.0f);
	m_angle = 0;
	m_scale = Vector2One;
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "image\\UniSoulClear.png";
	C2DImage::Initialize();
}

void Clear::Update() 
{
	this->SetupMatrices();
}
