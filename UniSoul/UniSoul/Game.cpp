#include "stdafx.h"
#include "Game.h"

EffectManager*			g_effectManager = NULL;
Pad g_pad;
DamageCollisionWorld* g_damageCollisionWorld = NULL;

Game::Game()
{
	g_soundEngine = NULL;
}

Game::~Game()
{
	Game::Terminate();
	m_stopFlag = FALSE;
	m_slowFlag = FALSE;
	m_deltaTime = 0.0f;
	delete g_soundEngine;
}

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	g_effectManager = new EffectManager;
	g_soundEngine = new CSoundEngine;

	this->CreateSprite();

	//サウンドエンジンの初期化。
	g_soundEngine->Init();
	//物理ワールドを初期化。
	m_physicsWorld.Initialize();
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
	//エネミーマネージャーの初期化。
	m_enemyManager.Initialize();
	//マップにあるオブジェクトの初期化。
	m_map.Initialize();
	//空の初期化。
	m_sky.Initialize();
	//レンダリングターゲットの作成。
	m_renderTarget.Create(2480,
		2480,
		1,		
		D3DFMT_A8R8G8B8,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0);
	//プレイヤーの体力バー初期化。
	m_playerHPBar.Initialize();
	//FPS表示用のフォントの初期化。
	m_font.Init();
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
		//現在設定されているレンダーターゲットをクリア。
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//影ユニティちゃんの描画。
		m_unitychan.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			TRUE);

		//マップにあるオブジェクトの影の描画。
		m_map.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			TRUE);


		//エネミーマネージャーの敵の影の描画。
		m_enemyManager.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
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
		FALSE);

	//マップにあるオブジェクトの描画。
	m_map.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//ユニティちゃんの描画。
	m_unitychan.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//エネミーマネージャーの描画。
	m_enemyManager.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//空の描画
	m_sky.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//体力バーの描画。
	m_playerHPBar.Render(m_pSprite);

	//FPSの計測された値を文字列に変換して描画。、
	double counter = m_stopWatch.GetElapsed();
	counter = 1.0f / counter;
	std::string FPS;
	FPS = "FPS = ";
	FPS = FPS + std::to_string(counter);
	m_font.Draw(FPS.c_str(), 1100, 0);

	int HP = m_unitychan.GetHP();
	std::string str;
	str = "HP ";
	str = str + std::to_string(HP);
	m_font.Draw(str.c_str(),0, 50);

	int Lv = m_unitychan.GetLv();
	std::string lv;
	lv = "Lv ";
	lv = lv + std::to_string(Lv);
	m_font.Draw(lv.c_str(), 0, 0);


	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	//バックバッファ(画面を書き換え中のバッファ)、フロントバッファ(画面に描画されているバッファ)。
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	m_stopWatch.Stop();
	
}

/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Game::Update()
{
	m_stopWatch.Start();

	m_deltaTime += 1.0f / 60.0f;

	//パッドの更新。
	g_pad.Update();

	switch (m_stopFlag)
	{
	case TRUE:
		//カメラの更新。
		m_camera.Update();
		break;
	case FALSE:
		if (m_slowFlag == TRUE)
		{
			if (0.0f == m_deltaTime / 2.0f)
			{
				//物理ワールドの更新。
				m_physicsWorld.Update();
				//サウンドエンジンの更新。
				g_soundEngine->Update();
				//ライトの更新。
				//m_light.Update();
				//ステージの更新。
				m_stage.Update();
				//ユニティちゃんの更新。
				m_unitychan.Update();
				//マップにあるオブジェクトの更新。
				m_map.Update();
				//エネミーマネージャーの更新。
				m_enemyManager.Update();
				//空の更新。
				m_sky.Update();
				//カメラの更新。
				m_camera.Update();
				//シャドウカメラの更新。
				m_shadowmapcamera.Update();
				//プレイヤーの体力バー更新。
				m_playerHPBar.Update();
			}
		}
		else
		{
			//物理ワールドの更新。
			m_physicsWorld.Update();
			//サウンドエンジンの更新。
			g_soundEngine->Update();
			//ライトの更新。
			//m_light.Update();
			//ステージの更新。
			m_stage.Update();
			//ユニティちゃんの更新。
			m_unitychan.Update();
			//マップにあるオブジェクトの更新。
			m_map.Update();
			//エネミーマネージャーの更新。
			m_enemyManager.Update();
			//空の更新。
			m_sky.Update();
			//カメラの更新。
			m_camera.Update();
			//シャドウカメラの更新。
			m_shadowmapcamera.Update();
			//プレイヤーの体力バー更新。
			m_playerHPBar.Update();
		}
		break;
	}
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
	m_enemyManager.Release();
}

HRESULT Game::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}