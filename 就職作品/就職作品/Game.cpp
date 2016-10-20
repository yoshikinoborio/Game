#include "stdafx.h"
#include "Game.h"

EffectManager*			g_effectManager = NULL;
Pad g_pad;

Game::Game()
{
}

Game::~Game()
{
	Game::Terminate();
}

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	g_effectManager = new EffectManager;

	//ライトを初期化。
	m_light.Initialize();
	//カメラの初期化。
	m_camera.Initialize();
	//シャドウカメラの初期化。
	m_shadowmapcamera.Initialize();
	//ステージの初期化。
	m_stage.Initialize();
	//ユニティちゃんの初期化。
	m_unitychan.Initialize();
	//マップにいるエネミーの初期化。
	m_enemy.Initialize();
	//マップにあるオブジェクトの初期化。
	m_map.Initialize();
	//空の初期化。
	m_sky.Initialize();
	//レンダリングターゲットの作成。
	m_renderTarget.Create(400,
		400,
		1,		
		D3DFMT_A8R8G8B8,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0);
	
}

//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
void Game::Draw()
{
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Turn on the zbuffer
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		LPDIRECT3DSURFACE9 renderTargetBackup;//バックバッファを指すポインタの退避場所。
		LPDIRECT3DSURFACE9 depthBufferBackup;//深度バッファを指すポインタの退避場所。
		g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);		//元々のレンダリングターゲットを保存。後で戻す必要があるので。
		g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);	//元々のデプスステンシルバッファを保存。後で戻す必要があるので。

		//ユニティちゃんをオフスクリーンレンダリング開始。
		//テクスチャをレンダリングターゲットに設定。
		g_pd3dDevice->SetRenderTarget(0, m_renderTarget.GetSurface());
		g_pd3dDevice->SetDepthStencilSurface(m_renderTarget.GetDepthStencilBuffer());

		//レンダリングターゲットを初期化。
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//影ユニティちゃんの描画。
		m_unitychan.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			m_light.GetDiffuseLightDirection(),
			m_light.GetDiffuseLightColor(),
			m_light.GetAmbientLight(),
			m_light.GetLight_Num(),
			TRUE);

		//マップにあるオブジェクトの影の描画
		m_map.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			m_light.GetDiffuseLightDirection(),
			m_light.GetDiffuseLightColor(),
			m_light.GetAmbientLight(),
			m_light.GetLight_Num(),
			TRUE);

		//マップにいるエネミーの影の描画
		m_enemy.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			m_light.GetDiffuseLightDirection(),
			m_light.GetDiffuseLightColor(),
			m_light.GetAmbientLight(),
			m_light.GetLight_Num(),
			TRUE);

		//保存しておいたバックバッファをレンダリングターゲットに設定。
		g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//戻す。
		//保存しておいたバックバッファの深度バッファを設定。
		g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//戻す。
		//オフスクリーンレンダリングした絵を描画。
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	//ステージの描画。
	m_stage.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num());

	//マップにあるオブジェクトの描画。
	m_map.Draw(m_camera.GetViewMatrix(),
	m_camera.GetProjectionMatrix(),
	m_light.GetDiffuseLightDirection(),
	m_light.GetDiffuseLightColor(),
	m_light.GetAmbientLight(),
	m_light.GetLight_Num(),
	FALSE);

	//ユニティちゃんの描画。
	m_unitychan.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num(),
		FALSE);

	//マップにいるエネミーの描画。
	m_enemy.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num(),
		FALSE);

	//空の描画
	m_sky.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num(),
		FALSE);

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	//バックバッファ(画面を書き換え中のバッファ)、フロントバッファ(画面に描画されているバッファ)。
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Game::Update()
{
	//ライトの更新。
	m_light.Update();
	//パッドの更新。
	g_pad.Update();
	//ステージの更新。
	m_stage.Update();
	//ユニティちゃんの更新。
	m_unitychan.Update();
	//マップにあるオブジェクトの更新。
	m_map.Update();
	//マップにいるエネミーの更新。
	m_enemy.Update();
	//空の更新。
	m_sky.Update();
	//カメラの更新。
	m_camera.Update();
	//シャドウカメラの更新。
	m_shadowmapcamera.Update();

}

//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Game::Terminate()
{
	m_unitychan.Release();
	m_stage.Release();
	m_sky.Release();
	g_pd3dDevice->Release();
}
