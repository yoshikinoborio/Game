#pragma once
#include "UnityChan.h"
#include "Camera.h"
#include "Pad.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "SkinModel.h"
#include "ShadowMapCamera.h"
#include "RenderTarget.h"
#include "SoundEngine.h"
//シーンの基底クラス。
class SceneBase
{
public:
	SceneBase();
	//派生クラスのデストラクタを呼ぶためにVirtual。
	virtual~SceneBase() {

	}
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Terminate();
	//ユニティちゃんのインスタンス取得。
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
	//シャドウカメラのインスタンスの取得。
	ShadowMapCamera* Getshadowmapcamera()
	{
		return &m_shadowmapcamera;
	}
	//レンダーターゲットのインスタンス取得。
	RenderTarget* GetRenderTarget()
	{
		return &m_renderTarget;
	}
protected:
	UnityChan m_unitychan;
	CSoundEngine*	m_soundEngine;
	Camera m_camera;
	ShadowMapCamera m_shadowmapcamera;
	RenderTarget	m_renderTarget;		//レンダーターゲットのインスタンス。
};

//どこでも使えるようにextern。
extern Pad g_pad;
extern EffectManager* g_effectManager;
extern SkinModelData g_orginSkinModelData;
extern EnemyManager* g_enemyManager;
