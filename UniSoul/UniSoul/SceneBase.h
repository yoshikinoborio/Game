#pragma once
#include "UnityChan.h"
#include "Camera.h"
#include "Pad.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "SkinModel.h"
#include "ShadowMapCamera.h"
#include "RenderTarget.h"
#include "SoundEngine.h"
//�V�[���̊��N���X�B
class SceneBase
{
public:
	SceneBase();
	//�h���N���X�̃f�X�g���N�^���ĂԂ��߂�Virtual�B
	virtual~SceneBase() {

	}
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Terminate();
	//���j�e�B�����̃C���X�^���X�擾�B
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
	//�V���h�E�J�����̃C���X�^���X�̎擾�B
	ShadowMapCamera* Getshadowmapcamera()
	{
		return &m_shadowmapcamera;
	}
	//�����_�[�^�[�Q�b�g�̃C���X�^���X�擾�B
	RenderTarget* GetRenderTarget()
	{
		return &m_renderTarget;
	}
protected:
	UnityChan m_unitychan;
	CSoundEngine*	m_soundEngine;
	Camera m_camera;
	ShadowMapCamera m_shadowmapcamera;
	RenderTarget	m_renderTarget;		//�����_�[�^�[�Q�b�g�̃C���X�^���X�B
};

//�ǂ��ł��g����悤��extern�B
extern Pad g_pad;
extern EffectManager* g_effectManager;
extern SkinModelData g_orginSkinModelData;
extern EnemyManager* g_enemyManager;
