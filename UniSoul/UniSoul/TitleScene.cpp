#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	m_soundEngine = NULL;
}


TitleScene::~TitleScene()
{
	Terminate();
}


void TitleScene::Initialize()
{
	m_soundEngine = new CSoundEngine;
	m_soundEngine->Init();
	m_title.Initialize();
	m_titleCursor.Initialize();
}

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

void TitleScene::Terminate()
{
}
