#pragma once
#include "SceneBase.h"
#include "Clear.h"

//�N���A�V�[���B
class ClearScene : public SceneBase
{
public:
	//�R���X�g���N�^�B
	ClearScene();

	//�f�X�g���N�^�B
	~ClearScene();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();

	//�`��B
	void Draw();
private:
	Clear m_clear;	//�Q�[���N���A��ʂ̉摜�B
};

//�ǂ��ł��g����悤��extern
extern ClearScene* clearScene;