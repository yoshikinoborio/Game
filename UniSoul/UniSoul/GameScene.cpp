#include "stdafx.h"
#include "GameScene.h"

//メインレンダリングターゲットを初期化。
void GameScene::InitMainRenderTarget()
{
	m_mainRenderTarget = new RenderTarget;
	m_mainRenderTarget->Create(
		FRAME_BUFFER_WITDH,			//レンダリングターゲットの幅と高さはフレームバッファと同じにしておく。(必ずしも同じである必要はない！！！)
		FRAME_BUFFER_HEIGHT,
		1,							//ミップマップレベル。これは1でいい。ミップマップ覚えてますか？
		D3DFMT_A8R8G8B8,			//レンダリングターゲットのフォーマット。今回はR8G8B8A8の32bitを指定する。
		D3DFMT_D24S8,				//デプスステンシルバッファのフォーマット。一般的に16bitと24bitフォーマットが使われることが多い。今回は24bitフォーマットを使う。
		D3DMULTISAMPLE_NONE,		//マルチサンプリングの種類。今回はマルチサンプリングは行わないのでD3DMULTISAMPLE_NONEでいい。
		0							//マルチサンプリングの品質レベル。今回はマルチサンプリングは行わないので0でいい。
	);
}

//板ポリの初期化。
void  GameScene::InitQuadPrimitive()
{
	m_quadPrimitive = new CPrimitive;
	//頂点の構造体。
	struct SVertex {
		float pos[4];	//頂点座標。
		float uv[2];		//UV座標。
	};
	//頂点バッファ。
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	//頂点レイアウト。頂点バッファの構造がどのようになっているかをGPUに教えるためのもの。
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//頂点ストリームの0番目の0バイト目からfloat型の4つ分のデータは座標(D3DDECLUSAGE_POSITION)であることを示している。
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//頂点ストリームの0番目の16バイト目からfloat型の2つ分のデータはUV座標(D3DDECLUSAGE_TEXCOORD)であることを示している。
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//インデックスバッファ。
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	m_quadPrimitive->Create(
		CPrimitive::eTriangleStrip,	//今回はプリミティブの種類はトライアングルストリップ。
		4,							//頂点の数。四角形の板ポリでトライアングルストリップなので４。
		sizeof(SVertex),			//頂点ストライド。一つの頂点の大きさ。単位はバイト。
		scShapeVertex_PT_Element,	//頂点レイアウト。
		vertexBuffer,				//頂点バッファ。
		4,							//インデックスの数。
		D3DFMT_INDEX16,				//インデックスバッファのフォーマット。今回は16bitフォーマットを指定する。
									//インデックスの数が65536以下の場合は16bitでいいが、それを超える場合はD3DFMT_INDEX32を指定する。
		indexBuffer					//インデックスバッファ。
	);
}


//メインレンダリングターゲットの内容を現在のレンダリングターゲットにコピー。
void GameScene::CopyMainRTToCurrentRT()
{
	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// αブレンドもいらない。
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	// 頂点ストリーム0番に板ポリの頂点バッファを設定する。
	g_pd3dDevice->SetStreamSource(
		0,												//頂点ストリームの番号。
		m_quadPrimitive->GetVertexBuffer()->GetBody(),	//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
														//今回は先頭から読み込むので0でいい。
		m_quadPrimitive->GetVertexBuffer()->GetStride()	//頂点一つ分のサイズ。単位はバイト。
	);

	//LPD3DXEFFECT shader = copyEffect;			//コピーを行うシェーダーを使う場合はこちら。
	LPD3DXEFFECT shader = m_monochromeEffect;		//モノクロフィルターをかける場合はこちらを使用する。
													//シェーダーを設定。
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//シーンテクスチャを設定する
	shader->SetTexture("g_tex", m_mainRenderTarget->GetTexture());
	//定数レジスタへの変更をコミットする。
	shader->CommitChanges();
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(m_quadPrimitive->GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(m_quadPrimitive->GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		m_quadPrimitive->GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。0でいい。
		0,										//最小の頂点インデックス。0でいい。
		m_quadPrimitive->GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。0でいい。
		m_quadPrimitive->GetNumPolygon()			//プリミティブの数。
	);
	shader->EndPass();
	shader->End();
	// 変更したレンダリングステートを元に戻す。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}


//ポストエフェクトに使う専用のシェーダーをロード。
void GameScene::LoadShaders()
{
	//コピーを行うシェーダーをロード。
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&m_copyEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
	//モノクロフィルターを行うシェーダーをロード。
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/MonochromeFilter.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&m_monochromeEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

GameScene::GameScene()
{
	m_soundEngine = NULL;
	g_effectManager = NULL;
	g_damageCollisionWorld = NULL;
	g_enemyManager = NULL;
}


GameScene::~GameScene()
{
	m_physicsWorld.Release();
	GameScene::Terminate();
	m_stopFlag = FALSE;
	//m_slowFlag = FALSE;
	//m_deltaTime = 0.0f;
	delete g_effectManager;
	delete g_damageCollisionWorld;
	delete g_enemyManager;
}

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void GameScene::Initialize()
{
	g_effectManager = new EffectManager;
	m_soundEngine = new CSoundEngine;
	g_damageCollisionWorld = new DamageCollisionWorld;
	g_enemyManager = new EnemyManager;
	//メインレンダリングターゲットを作成する。
	InitMainRenderTarget();
	//四角形の板ポリプリミティブを作成。
	InitQuadPrimitive();
	//シェーダーをロード。
	LoadShaders();
	//ダメージコリジョンの初期化。
	g_damageCollisionWorld->Start();
	//サウンドエンジンの初期化。
	m_soundEngine->Init();
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
	g_enemyManager->Initialize();
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
void GameScene::Draw()
{
	g_pd3dDevice->BeginScene();
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
	//現在設定されているレンダリングターゲットをクリア。
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
	g_enemyManager->Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
		m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
		TRUE);

	//保存しておいたバックバッファをレンダリングターゲットに設定。
	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//戻す。
																//保存しておいたバックバッファの深度バッファを設定。
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//戻す。
																//オフスクリーンレンダリングした絵を描画。
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();


	//ポストエフェクトに使うレンダリングターゲットの処理。
	//あとで戻すためにフレームバッファのレンダリングターゲットとデプスステンシルバッファのバックアップを取る。
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);

	//レンダリングターゲットをフレームバッファから変更する。
	g_pd3dDevice->SetRenderTarget(
		0,									//何番目のレンダリングターゲットを設定するかの引数。今回は0でいい。
		m_mainRenderTarget->GetSurface()	//変更するレンダリングターゲット。
	);
	// デプスステンシルバッファも変更する。
	g_pd3dDevice->SetDepthStencilSurface(m_mainRenderTarget->GetDepthStencilBuffer());
	// レンダリングターゲットをクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

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
	g_enemyManager->Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//空の描画
	m_sky.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//体力バーの描画。
	m_playerHPBar.Render();

	//FPSの計測された値を文字列に変換して描画。、
	double counter = m_stopWatch.GetElapsed();
	counter = 1.0f / counter;
	std::string FPS;
	FPS = "FPS = ";
	FPS = FPS + std::to_string(counter);
	m_font.Draw(FPS.c_str(), 1650, 0);

	int HP = m_unitychan.GetHP();
	std::string str;
	str = "HP ";
	str = str + std::to_string(HP);
	m_font.Draw(str.c_str(), 0, 50);

	int Lv = m_unitychan.GetLv();
	std::string lv;
	lv = "Lv ";
	lv = lv + std::to_string(Lv);
	m_font.Draw(lv.c_str(), 0, 0);

	//シーンの描画が完了したのでレンダリングターゲットをフレームバッファに戻す。
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);

	//参照カウンタが増えているので開放。
	frameBufferRT->Release();
	frameBufferDS->Release();

	//オフスクリーンレンダリングした絵をフレームバッファに貼り付ける。
	CopyMainRTToCurrentRT();

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
void GameScene::Update()
{
	m_stopWatch.Start();

	//m_deltaTime += 1.0f / 60.0f;

	//パッドの更新。
	g_pad.Update();

	switch (m_stopFlag)
	{
	case TRUE:
		//カメラの更新。
		m_camera.Update();
		break;
	case FALSE:
		//ダーメンコリジョンの更新。
		g_damageCollisionWorld->Update();
		//物理ワールドの更新。
		m_physicsWorld.Update();
		//サウンドエンジンの更新。
		m_soundEngine->Update();
		//ステージの更新。
		m_stage.Update();
		//ユニティちゃんの更新。
		m_unitychan.Update();
		//マップにあるオブジェクトの更新。
		m_map.Update();
		//エネミーマネージャーの更新。
		g_enemyManager->Update();
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
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void GameScene::Terminate()
{
	//g_pd3dDevice->Release();
}