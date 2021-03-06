#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"

//コンストラクタ。
TitleScene::TitleScene()
{
	m_soundEngine = NULL;
}

//デストラクタ。
TitleScene::~TitleScene()
{
	g_pd3dDevice->Release();
}

//初期化。
void TitleScene::Initialize()
{
	m_soundEngine = new CSoundEngine;
	//サウンドエンジンの初期化。
	m_soundEngine->Init();

	//タイトル画像初期化。
	m_title.Initialize();

	//カーソルの初期化。
	m_titleCursor.Initialize();

	//タイトル画面で流れるBGMの初期化。
	m_soundTitleBgm.InitStreaming("image/UniSoulOpBGM.wav");
	m_soundTitleBgm.Play(TRUE);
	m_soundTitleBgm.SetVolume(0.25f);
}


//更新。
void TitleScene::Update()
{
	//サウンドの更新。
	m_soundEngine->Update();

	//パッドの更新。
	g_pad.Update();

	//タイトル画像の更新。
	m_title.Update();

	//カーソルの更新。
	m_titleCursor.Update();

	//タイトル画面のBGMnの更新。
	m_soundTitleBgm.Update();

	if (g_pad.IsTrigger(enButtonA))
	{
		m_soundTitleBgm.Stop();
	}
}


//描画。
void TitleScene::Draw()
{
	g_pd3dDevice->BeginScene();
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//タイトル画面の描画。
	m_title.Render();
	//カーソルの描画。
	m_titleCursor.Render();

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	//バックバッファ(画面を書き換え中のバッファ)、フロントバッファ(画面に描画されているバッファ)。
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	
}

