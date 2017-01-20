#pragma once
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"
//�V�[���̊Ǘ��N���X�B
//class SceneBase;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	//�������B
	void Initialize();
	//�X�V�B
	void Update();
	//�`��B
	void Draw();
	//�V�[���̐؂�ւ��B
	void ChangeScene(const int& key);
	//����B
	void Terminate();
private:
	SceneBase* m_scenes;
	bool m_clearFlag;		//true�̓N���A�Afalse�̓Q�[���I�[�o�[�B
	int m_nextScene;
};

extern SceneManager* g_sceneManager;
extern SceneBase* g_pScenes;
