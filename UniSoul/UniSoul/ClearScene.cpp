#include "stdafx.h"
#include "SceneManager.h"
#include "ClearScene.h"

//�R���X�g���N�^�B
ClearScene::ClearScene()
{
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
}

//�X�V�B
void ClearScene::Update()
{
	//�Q�[���N���A��ʂ̉摜�̍X�V�B
	m_clear.Update();

	g_pad.Update();

	if (g_pad.IsTrigger(enButtonA))
	{
		g_sceneManager->ChangeScene(SceneNum::SceneNumTitle);
	}

	if (g_pad.IsTrigger(enButtonB))
	{
		PostQuitMessage(0);
	}
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