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
}

void TitleScene::Update()
{
	//�p�b�h�̍X�V�B
	g_pad.Update();
	m_soundEngine->Update();

	m_title.Update();
	if (g_pad.IsTrigger(enButtonA))
	{
		g_sceneManager->ChangeScene(2);
	}
}

void TitleScene::Draw()
{
	g_pd3dDevice->BeginScene();
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//�X�^�[�g��ʂ̕`��B
	m_title.Draw();

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	//�o�b�N�o�b�t�@(��ʂ������������̃o�b�t�@)�A�t�����g�o�b�t�@(��ʂɕ`�悳��Ă���o�b�t�@)�B
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	
}

void TitleScene::Terminate()
{
}
