#include "stdafx.h"
#include "Black.h"

Black::Black()
{
	m_alph = 255;
	m_alphFlag = FALSE;
}


Black::~Black()
{
}

void Black::Initialize()
{
	m_position = D3DXVECTOR2(FRAME_BUFFER_WITDH / 2, FRAME_BUFFER_HEIGHT / 2);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.5f, 1.5f);
	m_backColor = D3DCOLOR_ARGB(m_alph, 255, 255, 255);
	m_texFileName = "image\\Black.png";
	C2DImage::Initialize();
}

void Black::Update()
{
	//�t���O�����ĉ摜�̃��l���X�V�B
	if (m_alphFlag == FALSE)
	{
		//�����ɂ��Ă����B
		if (m_alph > 0)
		{
			m_alph -= 5;
		}
		else
		{
			m_alph = 0;
		}
	}
	else
	{
		//���񂾂��ʂ��������Ă����B
		if (m_alph<255)
		{
			m_alph += 3;
		}
		else
		{
			m_alph = 255;
		}
	}

	m_backColor = D3DCOLOR_ARGB(m_alph, 255, 255, 255);
	this->SetupMatrices();
}