#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	m_soundEngine = NULL;
}


TitleScene::~TitleScene()
{
	Terminate();
}


void TitleScene::Initialize()
{
	m_soundEngine = new CSoundEngine;
	m_soundEngine->Init();
	m_title.Initialize();
}

void TitleScene::Update()
{
	//パッドの更新。
	g_pad.Update();
	m_soundEngine->Update();

	m_title.Update();
	if (g_pad.IsTrigger(enButtonA))
	{
		g_sceneManager->ChangeScene(2);
	}
}

void TitleScene::Draw()
{
	g_pd3dDevice->BeginScene();
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//スタート画面の描画。
	m_title.Draw();

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	//バックバッファ(画面を書き換え中のバッファ)、フロントバッファ(画面に描画されているバッファ)。
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	
}

void TitleScene::Terminate()
{
}
