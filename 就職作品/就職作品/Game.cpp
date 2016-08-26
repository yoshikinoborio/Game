#include "stdafx.h"
#include "Game.h"

Pad g_pad;

Game::Game()
{
}

Game::~Game()
{
}

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	//ライトを初期化。
	light.Initialize();
	//プレイヤー初期化
	player.Initialize(g_pd3dDevice);
	//ステージの初期化
	stage.Initialize(g_pd3dDevice);
	//カメラの初期化
	camera.Initialize();
}

//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	//プレイヤーの描画
	player.Draw(g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetDiffuseLightDirection(),
		light.GetDiffuseLightColor(),
		light.GetAmbientLight(),
		light.GetLight_Num());

	//ステージの描画
	stage.Draw(g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetDiffuseLightDirection(),
		light.GetDiffuseLightColor(),
		light.GetAmbientLight(),
		light.GetLight_Num());

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	//バックバッファ(画面を書き換え中のバッファ)、フロントバッファ(画面に描画されているバッファ)
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Game::Update()
{
	//ライトの更新。
	light.Update();
	//プレイヤーの更新
	player.Update();
	//ステージの更新
	stage.Update();
	//カメラの更新
	camera.Update();
	//パッドの更新
	g_pad.Update();

}

//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Game::Terminate()
{
	player.Release();
	stage.Release();
}
