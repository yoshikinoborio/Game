#pragma once
#include "SceneBase.h"
#include "Stage.h"
#include "Light.h"
#include "Map.h"
#include "Sky.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "DirectXFont.h"
#include "Stopwatch.h"
#include "PlayerHPBar.h"
#include "Primitive.h"
#include "Physics.h"
#include "Bloom.h"
#include "ShadowMapCamera.h"

//ゲームシーン。
class GameScene : public SceneBase
{
public:
	//コンストラクタ。
	GameScene();
	//デストラクタ。
	~GameScene();
	//初期化
	void Initialize();
	//更新。
	void Update();
	//描画。
	void Draw();
	//解放。
	void Terminate();
	//メインレンダリングターゲットを初期化。
	void InitMainRenderTarget();
	//板ポリの初期化。
	void InitQuadPrimitive();
	//板ポリの描画。
	void DrawQuadPrimitive();
	//メインレンダリングターゲットの内容を現在のレンダリングターゲットにコピー。
	void CopyMainRTToCurrentRT();
	//ポストエフェクトに使う専用のシェーダーをロード。
	void LoadShaders();
	//ライトのインスタンスの取得。
	Light* GetLight()
	{
		return &m_light;
	}
	//ステージのインスタンスの取得。
	Stage* GatStage()
	{
		return &m_stage;
	}
	//TRUEにするとUpdateが止まる。
	void SetStopFlag(bool Flg)
	{
		m_stopFlag = Flg;
	}
	//TRUEにするとUpdateの更新回数を減らす。
	/*void SetSlowFlag(bool Flg)
	{
	m_slowFlag = Flg;
	}*/
	bool GetStopFlag()
	{
		return m_stopFlag;
	}
	//物理ワールドの取得。
	PhysicsWorld* GetPhysicsWorld()
	{
		return &m_physicsWorld;
	}
	//メインレンダリングターゲットの取得。
	RenderTarget* GetMainRenderTarget()
	{
		return m_mainRenderTarget;
	}
	//シャドウカメラのインスタンスの取得。
	ShadowMapCamera* Getshadowmapcamera()
	{
		return &m_shadowmapcamera;
	}
private:
	Stage			m_stage;
	Light			m_light;
	Map				m_map;
	Sky				m_sky;
	Enemy			m_enemy;
	bool			m_stopFlag;			//スタートボタンを押したらカメラ以外の処理を止まるフラグ。
	//bool			m_slowFlag;         //ヒットストップかどうかのフラグ。
	//float			m_deltaTime;
	CFont			m_font;
	CStopwatch		m_stopWatch;
	PlayerHPBar		m_playerHPBar;
	PhysicsWorld	m_physicsWorld;
	//ポストエフェクトを使うための変数たち。
	RenderTarget* m_mainRenderTarget;		//メインレンダリングターゲット。
	CPrimitive*	 m_quadPrimitive;
	LPD3DXEFFECT m_copyEffect;				//コピーを行うシェーダー。
	LPD3DXEFFECT m_monochromeEffect;		//モノクロフィルターをかけるシェーダー。
	Bloom        m_bloom;
	ShadowMapCamera m_shadowmapcamera;
};