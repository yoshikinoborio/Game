#include "stdafx.h"
#include "GameScene.h"

// �|����`��B
void GameScene::DrawQuadPrimitive()
{
	// ���_�X�g���[��0�Ԃɔ|���̒��_�o�b�t�@��ݒ肷��B
	g_pd3dDevice->SetStreamSource(
		0,												//���_�X�g���[���̔ԍ��B
		m_quadPrimitive->GetVertexBuffer()->GetBody(),	//���_�o�b�t�@�B
		0,												//���_�o�b�t�@�̓ǂݍ��݂��J�n����I�t�Z�b�g�̃o�C�g���B
														//����͐擪����ǂݍ��ނ̂�0�ł����B
		m_quadPrimitive->GetVertexBuffer()->GetStride()	//���_����̃T�C�Y�B�P�ʂ̓o�C�g�B
	);
	// �C���f�b�N�X�o�b�t�@��ݒ�B
	g_pd3dDevice->SetIndices(m_quadPrimitive->GetIndexBuffer()->GetBody());
	// ���_��`��ݒ肷��B
	g_pd3dDevice->SetVertexDeclaration(m_quadPrimitive->GetVertexDecl());
	//�@�������������̂ŕ`��B
	g_pd3dDevice->DrawIndexedPrimitive(
		m_quadPrimitive->GetD3DPrimitiveType(),	//�v���~�e�B�u�̎�ނ��w�肷��B
		0,										//�x�[�X���_�C���f�b�N�X�B0�ł����B
		0,										//�ŏ��̒��_�C���f�b�N�X�B0�ł����B
		m_quadPrimitive->GetNumVertex(),			//���_�̐��B
		0,										//�J�n�C���f�b�N�X�B0�ł����B
		m_quadPrimitive->GetNumPolygon()			//�v���~�e�B�u�̐��B
	);
}


//���C�������_�����O�^�[�Q�b�g���������B
void GameScene::InitMainRenderTarget()
{
	m_mainRenderTarget = new RenderTarget;
	m_mainRenderTarget->Create(
		FRAME_BUFFER_WITDH,			//�����_�����O�^�[�Q�b�g�̕��ƍ����̓t���[���o�b�t�@�Ɠ����ɂ��Ă����B(�K�����������ł���K�v�͂Ȃ��I�I�I)
		FRAME_BUFFER_HEIGHT,
		1,							//�~�b�v�}�b�v���x���B�����1�ł����B�~�b�v�}�b�v�o���Ă܂����H
		D3DFMT_A16B16G16R16F,			//�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g�B�����R8G8B8A8��32bit���w�肷��B
		D3DFMT_D24S8,				//�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B��ʓI��16bit��24bit�t�H�[�}�b�g���g���邱�Ƃ������B�����24bit�t�H�[�}�b�g���g���B
		D3DMULTISAMPLE_NONE,		//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		0							//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
	);
}

//�|���̏������B
void  GameScene::InitQuadPrimitive()
{
	m_quadPrimitive = new CPrimitive;
	//���_�̍\���́B
	struct SVertex {
		float pos[4];	//���_���W�B
		float uv[2];		//UV���W�B
	};
	//���_�o�b�t�@�B
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	//���_���C�A�E�g�B���_�o�b�t�@�̍\�����ǂ̂悤�ɂȂ��Ă��邩��GPU�ɋ����邽�߂̂��́B
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//���_�X�g���[����0�Ԗڂ�0�o�C�g�ڂ���float�^��4���̃f�[�^�͍��W(D3DDECLUSAGE_POSITION)�ł��邱�Ƃ������Ă���B
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//���_�X�g���[����0�Ԗڂ�16�o�C�g�ڂ���float�^��2���̃f�[�^��UV���W(D3DDECLUSAGE_TEXCOORD)�ł��邱�Ƃ������Ă���B
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//�C���f�b�N�X�o�b�t�@�B
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	m_quadPrimitive->Create(
		CPrimitive::eTriangleStrip,	//����̓v���~�e�B�u�̎�ނ̓g���C�A���O���X�g���b�v�B
		4,							//���_�̐��B�l�p�`�̔|���Ńg���C�A���O���X�g���b�v�Ȃ̂łS�B
		sizeof(SVertex),			//���_�X�g���C�h�B��̒��_�̑傫���B�P�ʂ̓o�C�g�B
		scShapeVertex_PT_Element,	//���_���C�A�E�g�B
		vertexBuffer,				//���_�o�b�t�@�B
		4,							//�C���f�b�N�X�̐��B
		D3DFMT_INDEX16,				//�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g�B�����16bit�t�H�[�}�b�g���w�肷��B
									//�C���f�b�N�X�̐���65536�ȉ��̏ꍇ��16bit�ł������A����𒴂���ꍇ��D3DFMT_INDEX32���w�肷��B
		indexBuffer					//�C���f�b�N�X�o�b�t�@�B
	);
}

//���C�������_�����O�^�[�Q�b�g�̓��e�����݂̃����_�����O�^�[�Q�b�g�ɃR�s�[�B
void GameScene::CopyMainRTToCurrentRT()
{
	// Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// ���u�����h������Ȃ��B
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	// ���_�X�g���[��0�Ԃɔ|���̒��_�o�b�t�@��ݒ肷��B
	g_pd3dDevice->SetStreamSource(
		0,												//���_�X�g���[���̔ԍ��B
		m_quadPrimitive->GetVertexBuffer()->GetBody(),	//���_�o�b�t�@�B
		0,												//���_�o�b�t�@�̓ǂݍ��݂��J�n����I�t�Z�b�g�̃o�C�g���B
														//����͐擪����ǂݍ��ނ̂�0�ł����B
		m_quadPrimitive->GetVertexBuffer()->GetStride()	//���_����̃T�C�Y�B�P�ʂ̓o�C�g�B
	);

	LPD3DXEFFECT shader = m_copyEffect;			//�R�s�[���s���V�F�[�_�[���g���ꍇ�͂�����B
	//LPD3DXEFFECT shader = m_monochromeEffect;		//���m�N���t�B���^�[��������ꍇ�͂�������g�p����B
													//�V�F�[�_�[��ݒ�B
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//�V�[���e�N�X�`����ݒ肷��
	shader->SetTexture("g_tex", m_mainRenderTarget->GetTexture());
	//�萔���W�X�^�ւ̕ύX���R�~�b�g����B
	shader->CommitChanges();
	// �C���f�b�N�X�o�b�t�@��ݒ�B
	g_pd3dDevice->SetIndices(m_quadPrimitive->GetIndexBuffer()->GetBody());
	// ���_��`��ݒ肷��B
	g_pd3dDevice->SetVertexDeclaration(m_quadPrimitive->GetVertexDecl());
	//�@�������������̂ŕ`��B
	g_pd3dDevice->DrawIndexedPrimitive(
		m_quadPrimitive->GetD3DPrimitiveType(),	//�v���~�e�B�u�̎�ނ��w�肷��B
		0,										//�x�[�X���_�C���f�b�N�X�B0�ł����B
		0,										//�ŏ��̒��_�C���f�b�N�X�B0�ł����B
		m_quadPrimitive->GetNumVertex(),			//���_�̐��B
		0,										//�J�n�C���f�b�N�X�B0�ł����B
		m_quadPrimitive->GetNumPolygon()			//�v���~�e�B�u�̐��B
	);
	shader->EndPass();
	shader->End();
	// �ύX���������_�����O�X�e�[�g�����ɖ߂��B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}


//�|�X�g�G�t�F�N�g�Ɏg����p�̃V�F�[�_�[�����[�h�B
void GameScene::LoadShaders()
{
	//�R�s�[���s���V�F�[�_�[�����[�h�B
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&m_copyEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
	//���m�N���t�B���^�[���s���V�F�[�_�[�����[�h�B
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/MonochromeFilter.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&m_monochromeEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

GameScene::GameScene()
{
	g_effectManager = new EffectManager;
	g_damageCollisionWorld = NULL;
	m_soundEngine = NULL;
	g_enemyManager = NULL;
}


GameScene::~GameScene()
{
	m_physicsWorld.Release();
	GameScene::Terminate();
	m_stopFlag = FALSE;
	delete g_enemyManager;
}

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void GameScene::Initialize()
{
	m_soundEngine = new CSoundEngine;
	g_damageCollisionWorld = new DamageCollisionWorld;
	g_enemyManager = new EnemyManager;
	//���C�������_�����O�^�[�Q�b�g���쐬����B
	InitMainRenderTarget();

	//�l�p�`�̔|���v���~�e�B�u���쐬�B
	InitQuadPrimitive();

	//�V�F�[�_�[�����[�h�B
	LoadShaders();

	//�_���[�W�R���W�����̏������B
	g_damageCollisionWorld->Start();

	//�T�E���h�G���W���̏������B
	m_soundEngine->Init();

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

	//�v���C���[�̏������B
	m_unitychan.Initialize();

	//�G�l�~�[�}�l�[�W���[�̏������B
	g_enemyManager->Initialize();

	//�}�b�v�ɂ���I�u�W�F�N�g�̏������B
	m_map.Initialize();

	//��̏������B
	m_sky.Initialize();

	//�����Ȃ������蔻��̍쐬�B
	//m_collisionCreat.Initialize();

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

	//YouDied�̏������B
	m_youDied.Initialize();

	//�u���b�N�A�E�g�̉摜�̏������B
	m_black.Initialize();

	//�{�X�̗̑̓o�[�̏������B
	m_bossEnemyHPBar.Initialize();

	//�{�X�̗̑͂�HP�o�[�̃t���[���̏������B
	m_bossEnemyHPBarFrame.Initialize();

	//�{�X�̗̑̓o�[�̔w�i�̍X�V�B
	m_bossEnemyHPBarBack.Initialize();

	//�{�X�̖��O�̏������B
	m_bossEnemyName.Initialize();

	//���X�|�[���n�_�̏������B
	m_respawn.Initialize();

	//FPS�\���p�̃t�H���g�̏������B
	m_font.Init();
}

//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
void GameScene::Draw()
{
	g_pd3dDevice->BeginScene();
	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	LPDIRECT3DSURFACE9 renderTargetBackup;//�o�b�N�o�b�t�@���w���|�C���^�̑ޔ��ꏊ�B
	LPDIRECT3DSURFACE9 depthBufferBackup;//�[�x�o�b�t�@���w���|�C���^�̑ޔ��ꏊ�B
	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);		//���X�̃����_�����O�^�[�Q�b�g��ۑ��B��Ŗ߂��K�v������̂ŁB
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);	//���X�̃f�v�X�X�e���V���o�b�t�@��ۑ��B��Ŗ߂��K�v������̂ŁB

	//�v���C���[���I�t�X�N���[�������_�����O�J�n�B
	//�e�N�X�`���������_�����O�^�[�Q�b�g�ɐݒ�B
	g_pd3dDevice->SetRenderTarget(0, m_renderTarget.GetSurface());
	g_pd3dDevice->SetDepthStencilSurface(m_renderTarget.GetDepthStencilBuffer());

	//�����_�����O�^�[�Q�b�g���������B
	//���ݐݒ肳��Ă��郌���_�����O�^�[�Q�b�g���N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	//�e�v���C���[�̕`��B
	m_unitychan.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
		m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
		TRUE);

	//�}�b�v�ɂ���I�u�W�F�N�g�̉e�̕`��B
	m_map.Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
	m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
	TRUE);


	//�G�l�~�[�}�l�[�W���[�̓G�̉e�̕`��B
	g_enemyManager->Draw(m_shadowmapcamera.GetShadowMapCameraViewMatrix(),
		m_shadowmapcamera.GetShadowMapCameraProjectionMatrix(),
		TRUE);

	//�ۑ����Ă������o�b�N�o�b�t�@�������_�����O�^�[�Q�b�g�ɐݒ�B
	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//�߂��B
	//�ۑ����Ă������o�b�N�o�b�t�@�̐[�x�o�b�t�@��ݒ�B
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//�߂��B
	//�I�t�X�N���[�������_�����O�����G��`��B
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();


	//�|�X�g�G�t�F�N�g�Ɏg�������_�����O�^�[�Q�b�g�̏����B
	//���ƂŖ߂����߂Ƀt���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���o�b�t�@�̃o�b�N�A�b�v�����B
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);

	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@����ύX����B
	g_pd3dDevice->SetRenderTarget(
		0,									//���Ԗڂ̃����_�����O�^�[�Q�b�g��ݒ肷�邩�̈����B�����0�ł����B
		m_mainRenderTarget->GetSurface()	//�ύX���郌���_�����O�^�[�Q�b�g�B
	);
	// �f�v�X�X�e���V���o�b�t�@���ύX����B
	g_pd3dDevice->SetDepthStencilSurface(m_mainRenderTarget->GetDepthStencilBuffer());
	// �����_�����O�^�[�Q�b�g���N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//��̕`��
	m_sky.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//�}�b�v�ɂ���I�u�W�F�N�g�̕`��B
	m_map.Draw(m_camera.GetViewMatrix(),
	m_camera.GetProjectionMatrix(),
	FALSE);

	//�G�l�~�[�}�l�[�W���[�̕`��B
	g_enemyManager->Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//�v���C���[�̕`��B
	m_unitychan.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//�X�e�[�W�̕`��B
	m_stage.Draw(m_camera.GetViewMatrix(),
		m_camera.GetProjectionMatrix(),
		FALSE);

	//�u���[���̕`��B
	m_bloom.Render();
	

	if (m_camera.GetCameraFreeFlag() == FALSE)
	{
		//�v���C���[�̗͕̑`��B
		m_playerHPBar.Render();

		if (m_unitychan.GetIsDead() == FALSE &&g_enemyManager->GetBoss().GetBossBattleFlag() == TRUE)
		{
			//�{�X�̗̑̓o�[�̔w�i�̍X�V�B
			m_bossEnemyHPBarBack.Render();

			//�{�X�̗̑̓o�[�̕`��B
			m_bossEnemyHPBar.Render();

			//�{�X�̗̑̓o�[�̃t���[���̕`��B
			m_bossEnemyHPBarFrame.Render();

			//�{�X�̖��O�̕`��B
			m_bossEnemyName.Render();
		}

		//�v���C���[��HP��\���B
		int HP = m_unitychan.GetHP();
		std::string str;
		str = "HP ";
		str = str + std::to_string(HP);
		m_font.Draw(str.c_str(), 0, 50);

		//�v���C���[�̃��x����\���B
		int Lv = m_unitychan.GetLv();
		std::string lv;
		lv = "Lv ";
		lv = lv + std::to_string(Lv);
		m_font.Draw(lv.c_str(), 0, 0);

	}
	else
	{
		//�t���[�J�������[�h�̕\���B
		std::string FreeCameraMode;
		FreeCameraMode = "FreeCameraMode";
		m_font.Draw(FreeCameraMode.c_str(), 0, 0);

		//�J�����̈ʒu��\���B
		{
			//�J������X���W��\���B
			D3DXVECTOR3 pos = m_camera.GetEyePt();
			std::string FreeCameraPositionX;
			FreeCameraPositionX = "Position.X:";
			FreeCameraPositionX = FreeCameraPositionX + std::to_string(pos.x);
			m_font.Draw(FreeCameraPositionX.c_str(), 0, 20);

			//�J������Y���W��\���B
			std::string FreeCameraPositionY;
			FreeCameraPositionY = "Position.Y:";
			FreeCameraPositionY = FreeCameraPositionY + std::to_string(pos.y);
			m_font.Draw(FreeCameraPositionY.c_str(), 0, 40);

			//�J������Z���W��\���B
			std::string FreeCameraPositionZ;
			FreeCameraPositionZ = "Position.Z:";
			FreeCameraPositionZ = FreeCameraPositionZ + std::to_string(pos.z);
			m_font.Draw(FreeCameraPositionZ.c_str(), 0, 60);
		}

		//�t���[�J�������[�h���ɑI������Ă��鐶������I�u�W�F�N�g�̐������擾�B
		int nowobject = m_camera.GetNowObject();
		//�������邽�߂ɑI������Ă���I�u�W�F�N�g�̖��O��\���B
		std::string Object;
		switch (nowobject)
		{
		case (int)GameObject::Skeleton:
			Object = "GameObject Enemy : Skeleton";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		case (int)GameObject::Goblin:
			Object = "GameObject Enemy : Goblin";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		case (int)GameObject::House_A:
			Object = "GameObject Object : House_A";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		case (int)GameObject::House_B:
			Object = "GameObject Object : House_B";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		case (int)GameObject::House_C:
			Object = "GameObject Object : House_C";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		case (int)GameObject::House_D:
			Object = "GameObject Object : House_D";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		case (int)GameObject::Yashi:
			Object = "GameObject Object : Yashi";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		case (int)GameObject::Player:
			Object = "GameObject Player : ���j�e�B�����";
			m_font.Draw(Object.c_str(), 0, 80);
			break;
		default:
			break;
		}
	}

	//YouDied�̕`��B
	m_youDied.Render();

	//�u���b�N�A�E�g�̉摜�̕`��B
	m_black.Render();

	//FPS�̌v�����ꂽ�l�𕶎���ɕϊ����ĕ`��B�A
	double counter = m_stopWatch.GetElapsed();
	counter = 1.0f / counter;
	std::string FPS;
	FPS = "FPS = ";
	FPS = FPS + std::to_string(counter);
	
#ifdef _DEBUG
	m_font.Draw(FPS.c_str(), 1650, 0);

#endif // DEBUG

	//�V�[���̕`�悪���������̂Ń����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);

	//�Q�ƃJ�E���^�������Ă���̂ŊJ���B
	frameBufferRT->Release();
	frameBufferDS->Release();

	//�I�t�X�N���[�������_�����O�����G���t���[���o�b�t�@�ɓ\��t����B
	CopyMainRTToCurrentRT();

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
void GameScene::Update()
{
	m_stopWatch.Start();

	//�p�b�h�̍X�V�B
	g_pad.Update();

	switch (m_stopFlag)
	{
	case TRUE:
		//�J�����̍X�V�B
		m_camera.Update();
		break;
	case FALSE:
		//�_�[�����R���W�����̍X�V�B
		g_damageCollisionWorld->Update();

		//�������[���h�̍X�V�B
		m_physicsWorld.Update();

		//�T�E���h�G���W���̍X�V�B
		m_soundEngine->Update();

		//�X�e�[�W�̍X�V�B
		m_stage.Update();

		//�v���C���[�̍X�V�B
		m_unitychan.Update();

		//�}�b�v�ɂ���I�u�W�F�N�g�̍X�V�B
		m_map.Update();

		//�G�l�~�[�}�l�[�W���[�̍X�V�B
		g_enemyManager->Update();

		//��̍X�V�B
		m_sky.Update();

		//�J�����̍X�V�B
		m_camera.Update();

		//�V���h�E�J�����̍X�V�B
		m_shadowmapcamera.Update();

		//�v���C���[�̗̑̓o�[�X�V�B
		m_playerHPBar.Update();

		//YouDied�̍X�V�B
		m_youDied.Update();

		//�u���b�N�A�E�g�̉摜�̍X�V�B
		m_black.Update();

		//���X�|�[���n�_�̍X�V�B
		m_respawn.Update();

		if (m_unitychan.GetIsDead() == FALSE && g_enemyManager->GetBoss().GetBossBattleFlag() == TRUE)
		{
			//�{�X�̗̑̓o�[�̍X�V�B
			m_bossEnemyHPBar.Update();

			//�{�X�̗̑̓o�[�̃t���[���̍X�V�B
			m_bossEnemyHPBarFrame.Update();

			//�{�X�̗̑̓o�[�̔w�i�̍X�V�B
			m_bossEnemyHPBarBack.Update();

			//�{�X�̖��O�̍X�V�B
			m_bossEnemyName.Update();
		}
	}
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void GameScene::Terminate()
{
	g_pd3dDevice->Release();
}