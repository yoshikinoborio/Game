#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"

//�R���X�g���N�^�B
TitleScene::TitleScene()
{
	m_soundEngine = NULL;
}

//�f�X�g���N�^�B
TitleScene::~TitleScene()
{
}

//�������B
void TitleScene::Initialize()
{
	m_soundEngine = new CSoundEngine;
	//�T�E���h�G���W���̏������B
	m_soundEngine->Init();

	//�^�C�g���摜�������B
	m_title.Initialize();

	//�J�[�\���̏������B
	m_titleCursor.Initialize();
}


//�X�V�B
void TitleScene::Update()
{
	//�T�E���h�̍X�V�B
	m_soundEngine->Update();
	//�p�b�h�̍X�V�B
	g_pad.Update();
	//�^�C�g���摜�̍X�V�B
	m_title.Update();
	//�J�[�\���̍X�V�B
	m_titleCursor.Update();
}


//�`��B
void TitleScene::Draw()
{
	g_pd3dDevice->BeginScene();
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//�^�C�g����ʂ̕`��B
	m_title.Render();
	//�J�[�\���̕`��B
	m_titleCursor.Render();

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	//�o�b�N�o�b�t�@(��ʂ������������̃o�b�t�@)�A�t�����g�o�b�t�@(��ʂɕ`�悳��Ă���o�b�t�@)�B
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	
}

