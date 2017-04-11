#pragma once
#include "SceneBase.h"
#include "Title.h"
#include "TitleCursor.h"
#include "SoundSource.h"

//�^�C�g���V�[��
class TitleScene : public SceneBase
{
public:
	//�R���X�g���N�^�B
	TitleScene();

	//�f�X�g���N�^�B
	~TitleScene();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();
	
	//�`��B
	void Draw();
private:
	Title			m_title;		//�^�C�g���̉摜�B
	TitleCursor		m_titleCursor;	//�^�C�g���ɕ\������Ă���J�[�\���B
	CSoundSource	m_soundTitleBgm;//�^�C�g����ʂ�BGM�B
};

//�ǂ��ł��g����悤��extern
extern TitleScene* titleScene;