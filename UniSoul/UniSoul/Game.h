#pragma once
#include "Camera.h"
#include "Stage.h"
#include "Light.h"
#include "Pad.h"
#include "EffectManager.h"
#include "UnityChan.h"
#include "ShadowMapCamera.h"
#include "RenderTarget.h"
#include "Map.h"
#include "Sky.h"
#include "Enemy.h"
#include "Physics.h"
#include "EnemyManager.h"

class Game
{
public:
	//�R���X�g���N�^�B
	Game();
	//�f�X�g���N�^�B
	~Game();
	//������
	void Initialize();
	//�X�V�B
	void Update();
	//�`��B
	void Draw();
	//����B
	void Terminate();
	//���j�e�B�����̃C���X�^���X�擾�B
	UnityChan* GetUnityChan()
	{
		return &m_unitychan;
	}
	//���C�g�̃C���X�^���X�̎擾�B
	Light* GetLight()
	{
		return &m_light;
	}
	//�J�����̃C���X�^���X�̎擾�B
	Camera* GetCamera()
	{
		return &m_camera;
	}
	//�X�e�[�W�̃C���X�^���X�̎擾�B
	Stage* GatStage()
	{
		return &m_stage;
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
	//�������[���h�̎擾�B
	PhysicsWorld* GetPhysicsWorld()
	{
		return &m_physicsWorld;
	}
private:
	UnityChan m_unitychan;
	Camera m_camera;
	Stage m_stage;
	Light m_light;
	ShadowMapCamera m_shadowmapcamera;
	RenderTarget	m_renderTarget;		//�����_�[�^�[�Q�b�g�̃C���X�^���X�B
	Map				m_map;
	Sky				m_sky;
	Enemy			m_enemy;
	PhysicsWorld	m_physicsWorld;
	EnemyManager	m_enemyManager;
};

//�ǂ��ł��g����悤��extern�B
extern Game* game;
extern Pad g_pad;				
extern EffectManager* g_effectManager;