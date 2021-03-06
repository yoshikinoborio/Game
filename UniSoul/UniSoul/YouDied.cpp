#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "YouDied.h"

//コンストラクタ。
YouDied::YouDied()
{
	//各変数の初期化。
	m_alph = 0;
	m_position = Vector2Zero;
	m_angle = 0;
	m_scale = Vector2Zero;
	m_backColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

//デストラクタ。
YouDied::~YouDied()
{
}

//初期化。
void YouDied::Initialize()
{
	m_position = D3DXVECTOR2(FRAME_BUFFER_WITDH / 2, FRAME_BUFFER_HEIGHT / 2 + 100);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.5f, 1.5f);
	m_backColor = D3DCOLOR_ARGB(m_alph, 255, 255, 255);
	m_texFileName = "image\\YOU DIED.png";
	C2DImage::Initialize();
}

//更新。
void YouDied::Update()
{
	YouDiedDrawProcess();
}

void YouDied::YouDiedDrawProcess()
{
	//フラグがTRUEになったらα値の計算開始。
	if (static_cast<GameScene*>(g_pScenes)->GetUnityChan()->GetIsDead() == TRUE)
	{
		//α値を少しずつ加算。
		//255を超えたら255に戻す。
		if (m_alph < 254)
		{
			m_alph += 2;
		}
		else
		{
			m_alph = 255;
			//画面を暗くしていく。
			static_cast<GameScene*>(g_pScenes)->GetBlack()->SetStartFlag(TRUE);
		}
	}

	m_backColor = D3DCOLOR_ARGB(m_alph, 255, 255, 255);

	this->SetupMatrices();
}