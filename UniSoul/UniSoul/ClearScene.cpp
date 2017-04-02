#include "stdafx.h"
#include "SceneManager.h"
#include "ClearScene.h"

//コンストラクタ。
ClearScene::ClearScene()
{
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
}

//更新。
void ClearScene::Update()
{
	//ゲームクリア画面の画像の更新。
	m_clear.Update();

	g_pad.Update();

	if (g_pad.IsTrigger(enButtonA))
	{
		g_sceneManager->ChangeScene(SceneNum::SceneNumTitle);
	}

	if (g_pad.IsTrigger(enButtonB))
	{
		PostQuitMessage(0);
	}
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