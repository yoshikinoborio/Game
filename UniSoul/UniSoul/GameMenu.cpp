#include "stdafx.h"
#include "GameMenu.h"
#include "SceneManager.h"


//コンストラクタ。
GameMenu::GameMenu()
{
	//ビューポートの各設定の初期化。
	m_viewPort.X = 0;
	m_viewPort.Y = 0;
	m_viewPort.Width = 0;
	m_viewPort.Height = 0;
	m_viewPort.MinZ = 0.0f;
	m_viewPort.MaxZ = 1.0f;
}

//デストラクタ。
GameMenu::~GameMenu()
{

}

//初期化。
void GameMenu::Initialize()
{
	//ビューポートの各設定の再設定。
	m_viewPort.X = 100;			//左上隅のx座標
	m_viewPort.Y = 100;			//左上隅のy座標
	m_viewPort.Width = 500;		//横幅
	m_viewPort.Height = 500;	//縦幅
	m_viewPort.MinZ = 0.0f;		//深度値の最小値　通常は0.0f
	m_viewPort.MaxZ = 1.0f;		//深度値の最大値  通常は1.0f
}

//更新。
void GameMenu::Update()
{
	if (g_pad.IsTrigger(enButtonStart))
	{

	}
}

//描画。
void GameMenu::Draw()
{
#ifdef _DEBUG
	//描画領域を変更（ビューポート行列）。
	g_pd3dDevice->SetViewport(&m_viewPort);

	//描画領域にした所を任意の色でクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	//プレイヤーの描画。
	g_pScenes->GetUnityChan()->Draw(static_cast<GameScene*>(g_pScenes)->GetCamera()->GetViewMatrix(),
		static_cast<GameScene*>(g_pScenes)->GetCamera()->GetProjectionMatrix(),
		FALSE);

#endif // !_DEBUG
}