#include "stdafx.h"
#include "SceneManager.h"

SceneManager* g_sceneManager;
SceneBase* g_pScenes;	// 現在のシーンのインスタンス(シーンごとに振る舞いが違うため、基底クラスのポインタ)。
EffectManager*			g_effectManager = NULL;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
EnemyManager* g_enemyManager = NULL;
Pad g_pad;

//コンストラクタ。
SceneManager::SceneManager()
{
	g_pScenes = NULL;
}

//デストラクタ。
SceneManager::~SceneManager()
{
	delete g_damageCollisionWorld;
}

//初期化。
void SceneManager::Initialize()
{
	SceneManager::ChangeScene(SceneNum::SceneNumGame);
}

//更新。
void SceneManager::Update()
{
	if (g_pScenes) {
		g_pScenes->Update();
	}
	if (m_nextScene != SceneNum::Invalid) {
		if (m_scenes != NULL)
		{
			delete g_pScenes;
		}
		if (m_nextScene == SceneNum::SceneNumTitle)
		{
			g_pScenes = new TitleScene;
		}
		if (m_nextScene == SceneNum::SceneNumGame)
		{
			g_pScenes = new GameScene;
		}
		if (m_nextScene == SceneNum::SceneNumClear)
		{
			g_pScenes = new ClearScene;
		}
		g_pScenes->Initialize();
		m_nextScene = SceneNum::Invalid;
	}
}

//描画。
void SceneManager::Draw()
{
	g_pScenes->Draw();
}

//シーンの切り替え。
void SceneManager::ChangeScene(const int& key)
{
	m_nextScene = key;
}

//解放。
void SceneManager::Terminate()
{
	g_pScenes->Terminate();
}