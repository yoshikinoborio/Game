//#pragma once
//#include "Camera.h"
//#include "Stage.h"
//#include "Light.h"
//#include "Pad.h"
//#include "EffectManager.h"
//#include "UnityChan.h"
//#include "ShadowMapCamera.h"
//#include "RenderTarget.h"
//#include "Map.h"
//#include "Sky.h"
//#include "Enemy.h"
//#include "Physics.h"
//#include "EnemyManager.h"
//#include "DirectXFont.h"
//#include "Stopwatch.h"
//#include "PlayerHPBar.h"
//#include "SoundEngine.h"
//#include "Primitive.h"
//
//class Game
//{
//public:
//	//コンストラクタ。
//	Game();
//	//デストラクタ。
//	~Game();
//	//初期化
//	void Initialize();
//	//更新。
//	void Update();
//	//描画。
//	void Draw();
//	//解放。
//	void Terminate();
//	//メインレンダリングターゲットを初期化。
//	void InitMainRenderTarget();
//	//板ポリの初期化。
//	void InitQuadPrimitive();
//	//メインレンダリングターゲットの内容を現在のレンダリングターゲットにコピー。
//	void CopyMainRTToCurrentRT();
//	//ポストエフェクトに使う専用のシェーダーをロード。
//	void LoadShaders();
//	//ユニティちゃんのインスタンス取得。
//	UnityChan* GetUnityChan()
//	{
//		return &m_unitychan;
//	}
//	//ライトのインスタンスの取得。
//	Light* GetLight()
//	{
//		return &m_light;
//	}
//	//カメラのインスタンスの取得。
//	Camera* GetCamera()
//	{
//		return &m_camera;
//	}
//	//ステージのインスタンスの取得。
//	Stage* GatStage()
//	{
//		return &m_stage;
//	}
//	//シャドウカメラのインスタンスの取得。
//	ShadowMapCamera* Getshadowmapcamera()
//	{
//		return &m_shadowmapcamera;
//	}
//	//レンダーターゲットのインスタンス取得。
//	RenderTarget* GetRenderTarget()
//	{
//		return &m_renderTarget;
//	}
//	//物理ワールドの取得。
//	PhysicsWorld* GetPhysicsWorld()
//	{
//		return &m_physicsWorld;
//	}
//	//TRUEにするとUpdateが止まる。
//	void SetStopFlag(bool Flg)
//	{
//		m_stopFlag = Flg;
//	}
//	//TRUEにするとUpdateの更新回数を減らす。
//	/*void SetSlowFlag(bool Flg)
//	{
//		m_slowFlag = Flg;
//	}*/
//	bool GetStopFlag()
//	{
//		return m_stopFlag;
//	}
//	CSoundEngine* GetsoundEngine()
//	{
//		return g_soundEngine;
//	}
//private:
//	UnityChan m_unitychan;
//	Camera m_camera;
//	Stage m_stage;
//	Light m_light;
//	ShadowMapCamera m_shadowmapcamera;
//	RenderTarget	m_renderTarget;		//レンダーターゲットのインスタンス。
//	Map				m_map;
//	Sky				m_sky;
//	Enemy			m_enemy;
//	PhysicsWorld	m_physicsWorld;
//	bool			m_stopFlag;			//スタートボタンを押したらカメラ以外の処理を止まるフラグ。
//	//bool			m_slowFlag;         //ヒットストップかどうかのフラグ。
//	//float			m_deltaTime;
//	CFont			m_font;
//	CStopwatch		m_stopWatch;
//	PlayerHPBar		m_playerHPBar;
//	CSoundEngine*	g_soundEngine;
//	//ポストエフェクトを使うための変数たち。
//	RenderTarget* m_mainRenderTarget;		//メインレンダリングターゲット。
//	CPrimitive*	m_quadPrimitive;			//四角形の板ポリプリミティブ。
//	LPD3DXEFFECT m_copyEffect;			//コピーを行うシェーダー。
//	LPD3DXEFFECT m_monochromeEffect;		//モノクロフィルターをかけるシェーダー。
//};
//
////どこでも使えるようにextern。
//extern Game* game;
//extern Pad g_pad;				
//extern EffectManager* g_effectManager;
//extern SkinModelData g_orginSkinModelData;
//extern EnemyManager* g_enemyManager;