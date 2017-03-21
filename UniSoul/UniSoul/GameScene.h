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
#include "YouDied.h"
#include "Black.h"
#include "CollisionCreat.h"
#include "BossEnemyHPBar.h"
#include "BossEnemyHPBarFrame.h"
#include "BossEnemyHPBarBack.h"
#include "BossEnemyName.h"

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

	bool GetStopFlag() const
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

	//プレイヤーが死んだ時に出る文字。
	YouDied* GetYouDied()
	{
		return &m_youDied;
	}

	//画面がだんだん見えなくなるor見えてくる処理に使う画像。
	Black* GetBlack()
	{
		return &m_black;
	}

	SkinModelDataResources* GetSkinModelDataResources()
	{
		return &m_skinModelDataResources;
	}

	Map* GetMap()
	{
		return &m_map;
	}
private:
	Stage					m_stage;					//地面。
	Light					m_light;					//ライト。
	Map						m_map;						//マップに配置されているオブジェクト。
	Sky						m_sky;						//スカイボックス。
	Enemy					m_enemy;					//エネミー。
	bool					m_stopFlag;					//スタートボタンを押したらカメラ以外の処理を止まるフラグ。
	CFont					m_font;						//DirectXのフォント機能。
	CStopwatch				m_stopWatch;
	PlayerHPBar				m_playerHPBar;				//プレイヤーの体力バー。
	PhysicsWorld			m_physicsWorld;				//物理ワールド。
	//ポストエフェクトを使うための変数たち。
	RenderTarget*			m_mainRenderTarget;			//メインレンダリングターゲット。
	CPrimitive*				m_quadPrimitive;
	LPD3DXEFFECT			m_copyEffect;				//コピーを行うシェーダー。
	LPD3DXEFFECT			m_monochromeEffect;			//モノクロフィルターをかけるシェーダー。
	Bloom					m_bloom;					//ブルーム。
	ShadowMapCamera			m_shadowmapcamera;			//シャドウカメラ(影描画用カメラ)。
	YouDied					m_youDied;					//プレイヤーが死んだ時に出る文字。
	Black					m_black;					//画面がだんだん見えなくなるor見えてくる処理に使う画像。
	//CollisionCreat	m_collisionCreat;				//見えない当たり判定。
	SkinModelDataResources	m_skinModelDataResources;	//スキンモデルリソース。
	BossEnemyHPBar			m_bossEnemyHPBar;			//ボスの体力バー。
	BossEnemyHPBarFrame		m_bossEnemyHPBarFrame;		//ボスの体力バーのフレーム。
	BossEnemyHPBarBack		m_bossEnemyHPBarBack;		//ボスの体力バーの背景。
	BossEnemyName			m_bossEnemyName;			//ボスの名前を表示。
};