#pragma once
#include "SceneBase.h"
#include "Title.h"
#include "TitleCursor.h"

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
	//�^�C�g���ɕ\������Ă���J�[�\���B
	TitleCursor m_titleCursor;
};

//�ǂ��ł��g����悤��extern
extern TitleScene* titleScene;