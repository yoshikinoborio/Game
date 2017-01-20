//#pragma once
//#include "Camera.h"
//#include "Stage.h"
//#include "Light.h"
//#include "Pad.h"
//#include "EffectManager.h"
//#include "UnityChan.h"
//#include "ShadowMapCamera.h"
//#include "RenderTarget.h"
//#include "Map.h"
//#include "Sky.h"
//#include "Enemy.h"
//#include "Physics.h"
//#include "EnemyManager.h"
//#include "DirectXFont.h"
//#include "Stopwatch.h"
//#include "PlayerHPBar.h"
//#include "SoundEngine.h"
//#include "Primitive.h"
//
//class Game
//{
//public:
//	//�R���X�g���N�^�B
//	Game();
//	//�f�X�g���N�^�B
//	~Game();
//	//������
//	void Initialize();
//	//�X�V�B
//	void Update();
//	//�`��B
//	void Draw();
//	//����B
//	void Terminate();
//	//���C�������_�����O�^�[�Q�b�g���������B
//	void InitMainRenderTarget();
//	//�|���̏������B
//	void InitQuadPrimitive();
//	//���C�������_�����O�^�[�Q�b�g�̓��e�����݂̃����_�����O�^�[�Q�b�g�ɃR�s�[�B
//	void CopyMainRTToCurrentRT();
//	//�|�X�g�G�t�F�N�g�Ɏg����p�̃V�F�[�_�[�����[�h�B
//	void LoadShaders();
//	//���j�e�B�����̃C���X�^���X�擾�B
//	UnityChan* GetUnityChan()
//	{
//		return &m_unitychan;
//	}
//	//���C�g�̃C���X�^���X�̎擾�B
//	Light* GetLight()
//	{
//		return &m_light;
//	}
//	//�J�����̃C���X�^���X�̎擾�B
//	Camera* GetCamera()
//	{
//		return &m_camera;
//	}
//	//�X�e�[�W�̃C���X�^���X�̎擾�B
//	Stage* GatStage()
//	{
//		return &m_stage;
//	}
//	//�V���h�E�J�����̃C���X�^���X�̎擾�B
//	ShadowMapCamera* Getshadowmapcamera()
//	{
//		return &m_shadowmapcamera;
//	}
//	//�����_�[�^�[�Q�b�g�̃C���X�^���X�擾�B
//	RenderTarget* GetRenderTarget()
//	{
//		return &m_renderTarget;
//	}
//	//�������[���h�̎擾�B
//	PhysicsWorld* GetPhysicsWorld()
//	{
//		return &m_physicsWorld;
//	}
//	//TRUE�ɂ����Update���~�܂�B
//	void SetStopFlag(bool Flg)
//	{
//		m_stopFlag = Flg;
//	}
//	//TRUE�ɂ����Update�̍X�V�񐔂����炷�B
//	/*void SetSlowFlag(bool Flg)
//	{
//		m_slowFlag = Flg;
//	}*/
//	bool GetStopFlag()
//	{
//		return m_stopFlag;
//	}
//	CSoundEngine* GetsoundEngine()
//	{
//		return g_soundEngine;
//	}
//private:
//	UnityChan m_unitychan;
//	Camera m_camera;
//	Stage m_stage;
//	Light m_light;
//	ShadowMapCamera m_shadowmapcamera;
//	RenderTarget	m_renderTarget;		//�����_�[�^�[�Q�b�g�̃C���X�^���X�B
//	Map				m_map;
//	Sky				m_sky;
//	Enemy			m_enemy;
//	PhysicsWorld	m_physicsWorld;
//	bool			m_stopFlag;			//�X�^�[�g�{�^������������J�����ȊO�̏������~�܂�t���O�B
//	//bool			m_slowFlag;         //�q�b�g�X�g�b�v���ǂ����̃t���O�B
//	//float			m_deltaTime;
//	CFont			m_font;
//	CStopwatch		m_stopWatch;
//	PlayerHPBar		m_playerHPBar;
//	CSoundEngine*	g_soundEngine;
//	//�|�X�g�G�t�F�N�g���g�����߂̕ϐ������B
//	RenderTarget* m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
//	CPrimitive*	m_quadPrimitive;			//�l�p�`�̔|���v���~�e�B�u�B
//	LPD3DXEFFECT m_copyEffect;			//�R�s�[���s���V�F�[�_�[�B
//	LPD3DXEFFECT m_monochromeEffect;		//���m�N���t�B���^�[��������V�F�[�_�[�B
//};
//
////�ǂ��ł��g����悤��extern�B
//extern Game* game;
//extern Pad g_pad;				
//extern EffectManager* g_effectManager;
//extern SkinModelData g_orginSkinModelData;
//extern EnemyManager* g_enemyManager;