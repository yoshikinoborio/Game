#include "stdafx.h"
#include "Game.h"

EffectManager*			g_effectManager = NULL;
Pad g_pad;

Game::Game()
{
}

Game::~Game()
{
	Game::Terminate();
}

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	g_effectManager = new EffectManager;

	//���C�g���������B
	m_light.Initialize();
	//�J�����̏������B
	m_camera.Initialize();
	//�V���h�E�J�����̏������B
	m_shadowmapcamera.Initialize();
	//�X�e�[�W�̏������B
	m_stage.Initialize();
	//���j�e�B�����̏������B
	m_unitychan.Initialize();
	//�}�b�v�ɂ���G�l�~�[�̏������B
	m_enemy.Initialize();
	//�}�b�v�ɂ���I�u�W�F�N�g�̏������B
	m_map.Initialize();
	//��̏������B
	m_sky.Initialize();
	//�����_�����O�^�[�Q�b�g�̍쐬�B
	m_renderTarget.Create(400,
		400,
		1,		
		D3DFMT_A8R8G8B8,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0);
	
}

//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
void Game::Draw()
{
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Turn on the zbuffer
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		LPDIRECT3DSURFACE9 renderTargetBackup;//�o�b�N�o�b�t�@���w���|�C���^�̑ޔ��ꏊ�B
		LPDIRECT3DSURFACE9 depthBufferBackup;//�[�x�o�b�t�@���w���|�C���^�̑ޔ��ꏊ�B
		g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);		//���X�̃����_�����O�^�[�Q�b�g��ۑ��B��Ŗ߂��K�v������̂ŁB
		g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);	//���X�̃f�v�X�X�e���V���o�b�t�@��ۑ��B��Ŗ߂��K�v������̂ŁB

		//���j�e�B�������I�t�X�N���[�������_�����O�J�n�B
		//�e�N�X�`���������_�����O�^�[�Q�b�g�ɐݒ�B
		g_pd3dDevice->SetRenderTarget(0, m_renderTarget.GetSurface());
		g_pd3dDevice->SetDepthStencilSurface(m_renderTarget.GetDepthStencilBuffer());

		//�����_�����O�^�[�Q�b�g���������B
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//�e���j�e�B�����̕`��B
		m_unitychan.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			m_light.GetDiffuseLightDirection(),
			m_light.GetDiffuseLightColor(),
			m_light.GetAmbientLight(),
			m_light.GetLight_Num(),
			TRUE);

		//�}�b�v�ɂ���I�u�W�F�N�g�̉e�̕`��
		m_map.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			m_light.GetDiffuseLightDirection(),
			m_light.GetDiffuseLightColor(),
			m_light.GetAmbientLight(),
			m_light.GetLight_Num(),
			TRUE);

		//�}�b�v�ɂ���G�l�~�[�̉e�̕`��
		m_enemy.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			m_light.GetDiffuseLightDirection(),
			m_light.GetDiffuseLightColor(),
			m_light.GetAmbientLight(),
			m_light.GetLight_Num(),
			TRUE);

		//�ۑ����Ă������o�b�N�o�b�t�@�������_�����O�^�[�Q�b�g�ɐݒ�B
		g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//�߂��B
		//�ۑ����Ă������o�b�N�o�b�t�@�̐[�x�o�b�t�@��ݒ�B
		g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//�߂��B
		//�I�t�X�N���[�������_�����O�����G��`��B
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	//�X�e�[�W�̕`��B
	m_stage.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num());

	//�}�b�v�ɂ���I�u�W�F�N�g�̕`��B
	m_map.Draw(m_camera.GetViewMatrix(),
	m_camera.GetProjectionMatrix(),
	m_light.GetDiffuseLightDirection(),
	m_light.GetDiffuseLightColor(),
	m_light.GetAmbientLight(),
	m_light.GetLight_Num(),
	FALSE);

	//���j�e�B�����̕`��B
	m_unitychan.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num(),
		FALSE);

	//�}�b�v�ɂ���G�l�~�[�̕`��B
	m_enemy.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num(),
		FALSE);

	//��̕`��
	m_sky.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		m_light.GetDiffuseLightDirection(),
		m_light.GetDiffuseLightColor(),
		m_light.GetAmbientLight(),
		m_light.GetLight_Num(),
		FALSE);

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	//�o�b�N�o�b�t�@(��ʂ������������̃o�b�t�@)�A�t�����g�o�b�t�@(��ʂɕ`�悳��Ă���o�b�t�@)�B
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*!-----------------------------------------------------------------------------
*@brief	�X�V�����B
-----------------------------------------------------------------------------*/
void Game::Update()
{
	//���C�g�̍X�V�B
	m_light.Update();
	//�p�b�h�̍X�V�B
	g_pad.Update();
	//�X�e�[�W�̍X�V�B
	m_stage.Update();
	//���j�e�B�����̍X�V�B
	m_unitychan.Update();
	//�}�b�v�ɂ���I�u�W�F�N�g�̍X�V�B
	m_map.Update();
	//�}�b�v�ɂ���G�l�~�[�̍X�V�B
	m_enemy.Update();
	//��̍X�V�B
	m_sky.Update();
	//�J�����̍X�V�B
	m_camera.Update();
	//�V���h�E�J�����̍X�V�B
	m_shadowmapcamera.Update();

}

//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Game::Terminate()
{
	m_unitychan.Release();
	m_stage.Release();
	m_sky.Release();
	g_pd3dDevice->Release();
}
