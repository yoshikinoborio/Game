#include "stdafx.h"
#include "SceneManager.h"
#include "ClearScene.h"

//�R���X�g���N�^�B
ClearScene::ClearScene()
{
	m_bgmVolume = 0.1f;
	m_soundEngine = NULL;
}

//�f�X�g���N�^�B
ClearScene::~ClearScene()
{
	g_pd3dDevice->Release();
}

//�������B
void ClearScene::Initialize()
{
	//�Q�[���N���A��ʂ̉摜�̏������B
	m_clear.Initialize();

	m_soundEngine = new CSoundEngine;
	//�T�E���h�G���W���̏������B
	m_soundEngine->Init();

	//�N���A�V�[����BGM�̏������B
	m_clearSceneBgm.InitStreaming("image/UniSoulGameClearBGM.wav");
	m_clearSceneBgm.Play(TRUE);
	m_clearSceneBgm.SetVolume(m_bgmVolume);
}

//�X�V�B
void ClearScene::Update()
{
	//�T�E���h�̍X�V�B
	m_soundEngine->Update();

	//�Q�[���N���A��ʂ̉摜�̍X�V�B
	m_clear.Update();

	//�Q�[���p�b�h�̍X�V�B
	g_pad.Update();

	//�^�C�g����ʂɖ߂�B
	if (g_pad.IsTrigger(enButtonA))
	{
		g_sceneManager->ChangeScene(SceneNum::SceneNumTitle);
	}

	//�Q�[������߂�B
	if (g_pad.IsTrigger(enButtonB))
	{
		PostQuitMessage(0);
	}

	if (m_bgmVolume < 0.25f)
	{
		m_bgmVolume += 0.01f;
	}

	//�N���A�V�[����BGM�̍X�V�B
	m_clearSceneBgm.Update();
}

//�`��B
void ClearScene::Draw()
{
	g_pd3dDevice->BeginScene();
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//�Q�[���N���A��ʂ̉摜�̕`��B
	m_clear.Render();
	
	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	//�o�b�N�o�b�t�@(��ʂ������������̃o�b�t�@)�A�t�����g�o�b�t�@(��ʂɕ`�悳��Ă���o�b�t�@)�B
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}