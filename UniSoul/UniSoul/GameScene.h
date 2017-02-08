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
	//TRUE�ɂ����Update�̍X�V�񐔂����炷�B
	/*void SetSlowFlag(bool Flg)
	{
	m_slowFlag = Flg;
	}*/
	bool GetStopFlag()
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
private:
	Stage			m_stage;
	Light			m_light;
	Map				m_map;
	Sky				m_sky;
	Enemy			m_enemy;
	bool			m_stopFlag;			//�X�^�[�g�{�^������������J�����ȊO�̏������~�܂�t���O�B
	//bool			m_slowFlag;         //�q�b�g�X�g�b�v���ǂ����̃t���O�B
	//float			m_deltaTime;
	CFont			m_font;
	CStopwatch		m_stopWatch;
	PlayerHPBar		m_playerHPBar;
	PhysicsWorld	m_physicsWorld;
	//�|�X�g�G�t�F�N�g���g�����߂̕ϐ������B
	RenderTarget* m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	CPrimitive*	 m_quadPrimitive;
	LPD3DXEFFECT m_copyEffect;				//�R�s�[���s���V�F�[�_�[�B
	LPD3DXEFFECT m_monochromeEffect;		//���m�N���t�B���^�[��������V�F�[�_�[�B
	Bloom        m_bloom;
	ShadowMapCamera m_shadowmapcamera;
};