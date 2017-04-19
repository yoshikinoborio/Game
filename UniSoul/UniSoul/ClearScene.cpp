#include "stdafx.h"
#include "SceneManager.h"
#include "ClearScene.h"

//コンストラクタ。
ClearScene::ClearScene()
{
	m_bgmVolume = 0.1f;
	m_soundEngine = NULL;
}

//デストラクタ。
ClearScene::~ClearScene()
{
	g_pd3dDevice->Release();
}

//初期化。
void ClearScene::Initialize()
{
	//ゲームクリア画面の画像の初期化。
	m_clear.Initialize();

	m_soundEngine = new CSoundEngine;
	//サウンドエンジンの初期化。
	m_soundEngine->Init();

	//クリアシーンのBGMの初期化。
	m_clearSceneBgm.InitStreaming("image/UniSoulGameClearBGM.wav");
	m_clearSceneBgm.Play(TRUE);
	m_clearSceneBgm.SetVolume(m_bgmVolume);
}

//更新。
void ClearScene::Update()
{
	//サウンドの更新。
	m_soundEngine->Update();

	//ゲームクリア画面の画像の更新。
	m_clear.Update();

	//ゲームパッドの更新。
	g_pad.Update();

	//タイトル画面に戻る。
	if (g_pad.IsTrigger(enButtonA))
	{
		g_sceneManager->ChangeScene(SceneNum::SceneNumTitle);
	}

	//ゲームをやめる。
	if (g_pad.IsTrigger(enButtonB))
	{
		PostQuitMessage(0);
	}

	if (m_bgmVolume < 0.25f)
	{
		m_bgmVolume += 0.01f;
	}

	//クリアシーンのBGMの更新。
	m_clearSceneBgm.Update();
}

//描画。
void ClearScene::Draw()
{
	g_pd3dDevice->BeginScene();
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//ゲームクリア画面の画像の描画。
	m_clear.Render();
	
	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	//バックバッファ(画面を書き換え中のバッファ)、フロントバッファ(画面に描画されているバッファ)。
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}