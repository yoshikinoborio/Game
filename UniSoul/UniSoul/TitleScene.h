#pragma once
#include "SceneBase.h"
#include "Title.h"

//�^�C�g���V�[��
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	//�������B
	void Initialize();
	//�X�V�B
	void Update();
	//�`��B
	void Draw();
	//����B
	void Terminate();
private:
	//�^�C�g���̉摜�B
	Title m_title;
};

//�ǂ��ł��g����悤��extern
extern TitleScene* titleScene;