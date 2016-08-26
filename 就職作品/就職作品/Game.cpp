#include "stdafx.h"
#include "Game.h"

Pad g_pad;

Game::Game()
{
}

Game::~Game()
{
}

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	//���C�g���������B
	light.Initialize();
	//�v���C���[������
	player.Initialize(g_pd3dDevice);
	//�X�e�[�W�̏�����
	stage.Initialize(g_pd3dDevice);
	//�J�����̏�����
	camera.Initialize();
}

//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	//�v���C���[�̕`��
	player.Draw(g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetDiffuseLightDirection(),
		light.GetDiffuseLightColor(),
		light.GetAmbientLight(),
		light.GetLight_Num());

	//�X�e�[�W�̕`��
	stage.Draw(g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetDiffuseLightDirection(),
		light.GetDiffuseLightColor(),
		light.GetAmbientLight(),
		light.GetLight_Num());

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	//�o�b�N�o�b�t�@(��ʂ������������̃o�b�t�@)�A�t�����g�o�b�t�@(��ʂɕ`�悳��Ă���o�b�t�@)
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*!-----------------------------------------------------------------------------
*@brief	�X�V�����B
-----------------------------------------------------------------------------*/
void Game::Update()
{
	//���C�g�̍X�V�B
	light.Update();
	//�v���C���[�̍X�V
	player.Update();
	//�X�e�[�W�̍X�V
	stage.Update();
	//�J�����̍X�V
	camera.Update();
	//�p�b�h�̍X�V
	g_pad.Update();

}

//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Game::Terminate()
{
	player.Release();
	stage.Release();
}
