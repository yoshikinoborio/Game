#include "stdafx.h"
#include "Game.h"

EffectManager*			g_effectManager = NULL;
Pad g_pad;
DamageCollisionWorld* g_damageCollisionWorld = NULL;

Game::Game()
{
	g_soundEngine = NULL;
}

Game::~Game()
{
	Game::Terminate();
	m_stopFlag = FALSE;
	m_slowFlag = FALSE;
	m_deltaTime = 0.0f;
	delete g_soundEngine;
}

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	g_effectManager = new EffectManager;
	g_soundEngine = new CSoundEngine;

	this->CreateSprite();

	//�T�E���h�G���W���̏������B
	g_soundEngine->Init();
	//�������[���h���������B
	m_physicsWorld.Initialize();
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
	//�G�l�~�[�}�l�[�W���[�̏������B
	m_enemyManager.Initialize();
	//�}�b�v�ɂ���I�u�W�F�N�g�̏������B
	m_map.Initialize();
	//��̏������B
	m_sky.Initialize();
	//�����_�����O�^�[�Q�b�g�̍쐬�B
	m_renderTarget.Create(2480,
		2480,
		1,		
		D3DFMT_A8R8G8B8,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0);
	//�v���C���[�̗̑̓o�[�������B
	m_playerHPBar.Initialize();
	//FPS�\���p�̃t�H���g�̏������B
	m_font.Init();
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
		//���ݐݒ肳��Ă��郌���_�[�^�[�Q�b�g���N���A�B
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//�e���j�e�B�����̕`��B
		m_unitychan.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			TRUE);

		//�}�b�v�ɂ���I�u�W�F�N�g�̉e�̕`��B
		m_map.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
			TRUE);


		//�G�l�~�[�}�l�[�W���[�̓G�̉e�̕`��B
		m_enemyManager.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
			m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
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
		FALSE);

	//�}�b�v�ɂ���I�u�W�F�N�g�̕`��B
	m_map.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//���j�e�B�����̕`��B
	m_unitychan.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//�G�l�~�[�}�l�[�W���[�̕`��B
	m_enemyManager.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//��̕`��
	m_sky.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//�̗̓o�[�̕`��B
	m_playerHPBar.Render(m_pSprite);

	//FPS�̌v�����ꂽ�l�𕶎���ɕϊ����ĕ`��B�A
	double counter = m_stopWatch.GetElapsed();
	counter = 1.0f / counter;
	std::string FPS;
	FPS = "FPS = ";
	FPS = FPS + std::to_string(counter);
	m_font.Draw(FPS.c_str(), 1100, 0);

	int HP = m_unitychan.GetHP();
	std::string str;
	str = "HP ";
	str = str + std::to_string(HP);
	m_font.Draw(str.c_str(),0, 50);

	int Lv = m_unitychan.GetLv();
	std::string lv;
	lv = "Lv ";
	lv = lv + std::to_string(Lv);
	m_font.Draw(lv.c_str(), 0, 0);


	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	//�o�b�N�o�b�t�@(��ʂ������������̃o�b�t�@)�A�t�����g�o�b�t�@(��ʂɕ`�悳��Ă���o�b�t�@)�B
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	m_stopWatch.Stop();
	
}

/*!-----------------------------------------------------------------------------
*@brief	�X�V�����B
-----------------------------------------------------------------------------*/
void Game::Update()
{
	m_stopWatch.Start();

	m_deltaTime += 1.0f / 60.0f;

	//�p�b�h�̍X�V�B
	g_pad.Update();

	switch (m_stopFlag)
	{
	case TRUE:
		//�J�����̍X�V�B
		m_camera.Update();
		break;
	case FALSE:
		if (m_slowFlag == TRUE)
		{
			if (0.0f == m_deltaTime / 2.0f)
			{
				//�������[���h�̍X�V�B
				m_physicsWorld.Update();
				//�T�E���h�G���W���̍X�V�B
				g_soundEngine->Update();
				//���C�g�̍X�V�B
				//m_light.Update();
				//�X�e�[�W�̍X�V�B
				m_stage.Update();
				//���j�e�B�����̍X�V�B
				m_unitychan.Update();
				//�}�b�v�ɂ���I�u�W�F�N�g�̍X�V�B
				m_map.Update();
				//�G�l�~�[�}�l�[�W���[�̍X�V�B
				m_enemyManager.Update();
				//��̍X�V�B
				m_sky.Update();
				//�J�����̍X�V�B
				m_camera.Update();
				//�V���h�E�J�����̍X�V�B
				m_shadowmapcamera.Update();
				//�v���C���[�̗̑̓o�[�X�V�B
				m_playerHPBar.Update();
			}
		}
		else
		{
			//�������[���h�̍X�V�B
			m_physicsWorld.Update();
			//�T�E���h�G���W���̍X�V�B
			g_soundEngine->Update();
			//���C�g�̍X�V�B
			//m_light.Update();
			//�X�e�[�W�̍X�V�B
			m_stage.Update();
			//���j�e�B�����̍X�V�B
			m_unitychan.Update();
			//�}�b�v�ɂ���I�u�W�F�N�g�̍X�V�B
			m_map.Update();
			//�G�l�~�[�}�l�[�W���[�̍X�V�B
			m_enemyManager.Update();
			//��̍X�V�B
			m_sky.Update();
			//�J�����̍X�V�B
			m_camera.Update();
			//�V���h�E�J�����̍X�V�B
			m_shadowmapcamera.Update();
			//�v���C���[�̗̑̓o�[�X�V�B
			m_playerHPBar.Update();
		}
		break;
	}
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
	m_enemyManager.Release();
}

HRESULT Game::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}