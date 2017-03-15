#pragma once
#include "UnityChan.h"
#include "Camera.h"
#include "Pad.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "SkinModel.h"
#include "RenderTarget.h"
#include "SoundEngine.h"
//シーンの基底クラス。
class SceneBase
{
public:
	//コンストラクタ。
	SceneBase();

	//派生クラスのデストラクタを呼ぶためにVirtual。
	virtual~SceneBase() {

	}

	//初期化。
	virtual void Initialize();

	//更新。
	virtual void Update();

	//描画。
	virtual void Draw();

	//解放。
	virtual void Terminate();

	//プレイヤーのインスタンス取得。
	UnityChan* GetUnityChan()
	{
		return &m_unitychan;
	}

	//カメラのインスタンスの取得。
	Camera* GetCamera()
	{
		return &m_camera;
	}

	//サウンドエンジンのインスタンス取得。
	CSoundEngine* GetsoundEngine()
	{
		return m_soundEngine;
	}

	//レンダーターゲットのインスタンス取得。
	RenderTarget* GetRenderTarget()
	{
		return &m_renderTarget;
	}

protected:
	UnityChan		m_unitychan;		//プレイヤーのインスタンス。
	CSoundEngine*	m_soundEngine;		//サウンドエンジンのインスタンス。
	Camera			m_camera;			//ゲームカメラのインスタンス。
	RenderTarget	m_renderTarget;		//レンダーターゲットのインスタンス。
};

//どこでも使えるようにextern。
extern Pad g_pad;
extern EffectManager* g_effectManager;
extern SkinModelData g_orginSkinModelData;
extern EnemyManager* g_enemyManager;
