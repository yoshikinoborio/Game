#pragma once
#include "UnityChan.h"
#include "Camera.h"
#include "Pad.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "SkinModel.h"
#include "RenderTarget.h"
#include "SoundEngine.h"
//�V�[���̊��N���X�B
class SceneBase
{
public:
	//�R���X�g���N�^�B
	SceneBase();

	//�h���N���X�̃f�X�g���N�^���ĂԂ��߂�Virtual�B
	virtual~SceneBase() {

	}

	//�������B
	virtual void Initialize();

	//�X�V�B
	virtual void Update();

	//�`��B
	virtual void Draw();

	//����B
	virtual void Terminate();

	//�v���C���[�̃C���X�^���X�擾�B
	UnityChan* GetUnityChan()
	{
		return &m_unitychan;
	}

	//�J�����̃C���X�^���X�̎擾�B
	Camera* GetCamera()
	{
		return &m_camera;
	}

	//�T�E���h�G���W���̃C���X�^���X�擾�B
	CSoundEngine* GetsoundEngine()
	{
		return m_soundEngine;
	}

	//�����_�[�^�[�Q�b�g�̃C���X�^���X�擾�B
	RenderTarget* GetRenderTarget()
	{
		return &m_renderTarget;
	}

protected:
	UnityChan		m_unitychan;		//�v���C���[�̃C���X�^���X�B
	CSoundEngine*	m_soundEngine;		//�T�E���h�G���W���̃C���X�^���X�B
	Camera			m_camera;			//�Q�[���J�����̃C���X�^���X�B
	RenderTarget	m_renderTarget;		//�����_�[�^�[�Q�b�g�̃C���X�^���X�B
};

//�ǂ��ł��g����悤��extern�B
extern Pad g_pad;
extern EffectManager* g_effectManager;
extern SkinModelData g_orginSkinModelData;
extern EnemyManager* g_enemyManager;
