#pragma once
#include "SceneBase.h"
#include "Stage.h"
#include "Light.h"
#include "Map.h"
#include "Sky.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "DirectXFont.h"
#include "Stopwatch.h"
#include "PlayerHPBar.h"
#include "Primitive.h"
#include "Physics.h"
#include "Bloom.h"
#include "ShadowMapCamera.h"
#include "YouDied.h"
#include "Black.h"
#include "CollisionCreat.h"
#include "BossEnemyHPBar.h"
#include "BossEnemyHPBarFrame.h"
#include "BossEnemyHPBarBack.h"
#include "BossEnemyName.h"

//�Q�[���V�[���B
class GameScene : public SceneBase
{
public:
	//�R���X�g���N�^�B
	GameScene();

	//�f�X�g���N�^�B
	~GameScene();

	//������
	void Initialize();

	//�X�V�B
	void Update();

	//�`��B
	void Draw();

	//����B
	void Terminate();

	//���C�������_�����O�^�[�Q�b�g���������B
	void InitMainRenderTarget();

	//�|���̏������B
	void InitQuadPrimitive();

	//�|���̕`��B
	void DrawQuadPrimitive();

	//���C�������_�����O�^�[�Q�b�g�̓��e�����݂̃����_�����O�^�[�Q�b�g�ɃR�s�[�B
	void CopyMainRTToCurrentRT();

	//�|�X�g�G�t�F�N�g�Ɏg����p�̃V�F�[�_�[�����[�h�B
	void LoadShaders();

	//���C�g�̃C���X�^���X�̎擾�B
	Light* GetLight()
	{
		return &m_light;
	}

	//�X�e�[�W�̃C���X�^���X�̎擾�B
	Stage* GatStage()
	{
		return &m_stage;
	}

	//TRUE�ɂ����Update���~�܂�B
	void SetStopFlag(bool Flg) 
	{
		m_stopFlag = Flg;
	}

	bool GetStopFlag() const
	{
		return m_stopFlag;
	}

	//�������[���h�̎擾�B
	PhysicsWorld* GetPhysicsWorld()
	{
		return &m_physicsWorld;
	}

	//���C�������_�����O�^�[�Q�b�g�̎擾�B
	RenderTarget* GetMainRenderTarget()
	{
		return m_mainRenderTarget;
	}

	//�V���h�E�J�����̃C���X�^���X�̎擾�B
	ShadowMapCamera* Getshadowmapcamera()
	{
		return &m_shadowmapcamera;
	}

	//�v���C���[�����񂾎��ɏo�镶���B
	YouDied* GetYouDied()
	{
		return &m_youDied;
	}

	//��ʂ����񂾂񌩂��Ȃ��Ȃ�or�����Ă��鏈���Ɏg���摜�B
	Black* GetBlack()
	{
		return &m_black;
	}

	SkinModelDataResources* GetSkinModelDataResources()
	{
		return &m_skinModelDataResources;
	}

	Map* GetMap()
	{
		return &m_map;
	}
private:
	Stage					m_stage;					//�n�ʁB
	Light					m_light;					//���C�g�B
	Map						m_map;						//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�B
	Sky						m_sky;						//�X�J�C�{�b�N�X�B
	Enemy					m_enemy;					//�G�l�~�[�B
	bool					m_stopFlag;					//�X�^�[�g�{�^������������J�����ȊO�̏������~�܂�t���O�B
	CFont					m_font;						//DirectX�̃t�H���g�@�\�B
	CStopwatch				m_stopWatch;
	PlayerHPBar				m_playerHPBar;				//�v���C���[�̗̑̓o�[�B
	PhysicsWorld			m_physicsWorld;				//�������[���h�B
	//�|�X�g�G�t�F�N�g���g�����߂̕ϐ������B
	RenderTarget*			m_mainRenderTarget;			//���C�������_�����O�^�[�Q�b�g�B
	CPrimitive*				m_quadPrimitive;
	LPD3DXEFFECT			m_copyEffect;				//�R�s�[���s���V�F�[�_�[�B
	LPD3DXEFFECT			m_monochromeEffect;			//���m�N���t�B���^�[��������V�F�[�_�[�B
	Bloom					m_bloom;					//�u���[���B
	ShadowMapCamera			m_shadowmapcamera;			//�V���h�E�J����(�e�`��p�J����)�B
	YouDied					m_youDied;					//�v���C���[�����񂾎��ɏo�镶���B
	Black					m_black;					//��ʂ����񂾂񌩂��Ȃ��Ȃ�or�����Ă��鏈���Ɏg���摜�B
	//CollisionCreat	m_collisionCreat;				//�����Ȃ������蔻��B
	SkinModelDataResources	m_skinModelDataResources;	//�X�L�����f�����\�[�X�B
	BossEnemyHPBar			m_bossEnemyHPBar;			//�{�X�̗̑̓o�[�B
	BossEnemyHPBarFrame		m_bossEnemyHPBarFrame;		//�{�X�̗̑̓o�[�̃t���[���B
	BossEnemyHPBarBack		m_bossEnemyHPBarBack;		//�{�X�̗̑̓o�[�̔w�i�B
	BossEnemyName			m_bossEnemyName;			//�{�X�̖��O��\���B
};