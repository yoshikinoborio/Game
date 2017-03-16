#include "stdafx.h"
#include "SceneManager.h"

SceneManager* g_sceneManager;
SceneBase* g_pScenes;	// 現在のシーンのインスタンス(シーンごとに振る舞いが違うため、基底クラスのポインタ)。
EffectManager*			g_effectManager = NULL;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
EnemyManager* g_enemyManager = NULL;
Pad g_pad;

SceneManager::SceneManager()
{
	g_pScenes = NULL;
	m_nextScene = -1;
}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize()
{
	SceneManager::ChangeScene(1);
}

void SceneManager::Update()
{
	if (g_pScenes) {
		g_pScenes->Update();
	}
	if (m_nextScene != -1) {
		if (g_pScenes != NULL)
		{
			delete g_pScenes;
		}
		if (m_nextScene == 1)
		{
			g_pScenes = new TitleScene;
		}
		if (m_nextScene == 2)
		{
			g_pScenes = new GameScene;
		}
		g_pScenes->Initialize();
		m_nextScene = -1;
	}
}

void SceneManager::Draw()
{
	g_pScenes->Draw();
}

void SceneManager::ChangeScene(int key)
{
	m_nextScene = key;
}

void SceneManager::Terminate()
{
	g_pScenes->Terminate();
}