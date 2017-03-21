#include "stdafx.h"
#include "SceneManager.h"

SceneManager* g_sceneManager;
SceneBase* g_pScenes;	// ���݂̃V�[���̃C���X�^���X(�V�[�����ƂɐU�镑�����Ⴄ���߁A���N���X�̃|�C���^)�B
EffectManager*			g_effectManager = NULL;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
EnemyManager* g_enemyManager = NULL;
Pad g_pad;

//�R���X�g���N�^�B
SceneManager::SceneManager()
{
	g_pScenes = NULL;
}

//�f�X�g���N�^�B
SceneManager::~SceneManager()
{
	delete g_damageCollisionWorld;
}

//�������B
void SceneManager::Initialize()
{
	SceneManager::ChangeScene(SceneNum::SceneNumGame);
}

//�X�V�B
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

//�`��B
void SceneManager::Draw()
{
	g_pScenes->Draw();
}

//�V�[���̐؂�ւ��B
void SceneManager::ChangeScene(const int& key)
{
	m_nextScene = key;
}

//����B
void SceneManager::Terminate()
{
	g_pScenes->Terminate();
}