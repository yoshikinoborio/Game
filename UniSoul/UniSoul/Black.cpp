#include "stdafx.h"
#include "Black.h"
#include "SceneManager.h"

//コンストラクタ。
Black::Black()
{
	//各変数の初期化。
	m_alph = 255;
	m_alphFlag = FALSE;
	m_position = D3DXVECTOR2(0.0f, 0.0f);
	m_angle = 0;
	m_scale = D3DXVECTOR2(0.0f, 0.0f);
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//デストラクタ。
Black::~Black()
{
}

//初期化。
void Black::Initialize()
{
	m_position = D3DXVECTOR2(FRAME_BUFFER_WITDH / 2, FRAME_BUFFER_HEIGHT / 2);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.5f, 1.5f);
	m_backColor = D3DCOLOR_ARGB(m_alph, 255, 255, 255);
	m_texFileName = "image\\Black.png";
	C2DImage::Initialize();
}

//更新。
void Black::Update()
{
	//フラグを見て画像のα値を更新。
	if (m_alphFlag == FALSE)
	{
		//透明にしていく。
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
		//だんだん画面を黒くしていく。
		if (m_alph<255)
		{
			m_alph += 3;
		}
		else
		{
			m_alph = 255;
			g_sceneManager->ChangeScene(SceneNum::SceneNumTitle);
		}
	}


	m_backColor = D3DCOLOR_ARGB(m_alph, 255, 255, 255);
	this->SetupMatrices();
}