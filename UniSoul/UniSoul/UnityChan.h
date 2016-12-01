#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"
#include "ParticleEmitter.h"
#include "SoundSource.h"
#include "Light.h"
#define WALKSPEED 0.02f*60.0f	//�����X�s�[�h�B
#define RUNSPEED 0.2f*60.0f	//����X�s�[�h�B
#define MAX_RUN 0.6f*60.0f	//�����܂ł̏���l�B
#define MAX_LEVEL 100

class CParticleEmitter;
class Camera;

class UnityChan : public AnimationModel3D
{
public:
	UnityChan();
	~UnityChan();
	//�������B
	void Initialize();
	//�X�V�B
	void Update()override;
	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	//����B
	void Release();
	//�p�b�h�ɂ��J�����̉��Ɉړ����鏈���B
	void PadMove();
	//�����Ă����Ԃł̏����B
	void StateMove();
	//�W�����v�����B
	void Jump();
	D3DXVECTOR3 GetUnityChanPos()
	{
		return m_position;
	}
	D3DXMATRIX GetUnityChanWorld()
	{
		return m_world;
	}
	D3DXVECTOR3 GetUnityiChanScale()
	{
		return m_scale;
	}
	D3DXQUATERNION GetUnityiChanRotation()
	{
		return m_rotation;
	}
	D3DXVECTOR3 GetUniDir()
	{
		return m_UniDir;
	}
	//HP�̎擾�B
	int GetHP()
	{
		return m_hp;
	}
	//�ő�HP�̎擾�B
	int GetMaxHP()
	{
		return m_maxhp;
	}
	//�o���l�̉��Z
	void AddPlayerEXP(int EXP)
	{
		m_getEXP += EXP;
	}
	//�v���C���[�̃��x���̎擾�B
	int GetLv()
	{
		return m_lv;
	}
	void Damage();
	//�v���C���[�ōĐ������A�j���[�V�����̎�ށB
	enum PlayerAnimationNo {
		AnimationWait_00 = 0,	//�ҋ@(����)�B
		AnimationWalk,		//�����B
		AnimationRun,		//����B
		AnimationWait_01,	//�ҋ@(�r�L�΂�)�B
		AnimationWait_02,	//�ҋ@(�N���N��)�B
		AnimationSLID,		//�X���C�f�B���O�B
		AnimationBackStep,	//�o�b�N�X�e�b�v�B
		AnimationFall,		//�������B
		AnimationLanding,	//���n�B
		AnimationJump,		//�W�����v�B
		AnimationPunch,		//�p���`�B
		AnimationRKick,		//�E��i�R��B
		AnimationRotationKick,//�񂵏R��B
		AnimationSomersault,//�T�}�[�\���g�B
		AnimationFightingPause,//�퓬�ł̑ҋ@�B
		AnimationFightingRun,//�퓬�ł̑���B
		AnimationDaiLanding,//��������̒��n�B
		AnimationDownFly,	//������сB
		AnimationDamage_00,//�_���[�W�B
	};

	//�v���C���[�̏�ԑJ�ڂ̎�ށB
	enum PlayerState {
		StateInvalid = -1,
		StateWait_00,		//�ҋ@(����)�B
		StateWait_01,		//�ҋ@(�r�L�΂�)�B
		StateWait_02,		//�ҋ@(�N���N��)�B
		StateWalk,          //�����B
		StateRun,			//����B
		StateSLID,			//�X���C�f�B���O�B
		StateBackStep,		//�o�b�N�X�e�b�v�B
		StateFall,			//�����B
		StateLanding,		//���n�B
		StateJump,			//�W�����v�B
		StateDamage,		//�_���[�W���󂯂Ă���B
		StateDead,			//����ł���B
		StateAttack,		//�U�����B
	};

private:
	D3DXVECTOR3		m_position;					//���W�B
	D3DXVECTOR3     m_scale;					//�X�P�[���B
	D3DXMATRIX		m_world;					//���[���h�s��B
	Camera*         m_camera;					//�J�����̃C���X�^���X�B
	int				m_currentAnimSetNo;			//���ݍĐ����Ă���A�j���[�V�����B
	PlayerState     m_state;					//�v���C���[�̏�ԁB
	D3DXQUATERNION  m_rotation;					//��]�s��B
	D3DXVECTOR3     m_moveDir;					//�J�������狁�߂������B
	D3DXVECTOR3     m_move;						//�ړ��ʁB
	float           m_moveSpeed;				//�ړ����x(�������Ƒ��鎞�̑��x�����p)�B
	float           m_waitAnimetionChangeTime;	//�ҋ@�A�j���[�V�����̐؂�ւ����ԁB
	float			m_currentAngleY;			//���݂̕����B
	float			m_targetAngleY;				//�������������B
	bool			m_isTurn;					//��]�t���O�B
	float           m_saveLStickX;				//���X�e�B�b�N�̍��E�̓��͗ʂ��i�[�B
	float			m_saveLStickY;				//���X�e�B�b�N�̑O��̓��͗ʂ��i�[�B
	CharacterController m_characterController;	//�L�����N�^�R���g���[���B
	float			m_height;					//���j�e�B�����̍����B
	float			m_radius;					//���j�e�B�����̔��a�B
	bool			m_battleFlag;				//�o�g�������̃t���O�B
	float			m_fallTimer;				//�������ԁB
	int				m_hp;						//�q�b�g�|�C���g�B
	int				m_maxhp;					//�ő�q�b�g�|�C���g�B
	D3DXVECTOR3		m_UniDir;					//���j�e�B�����̈ړ��x�N�g��(�G�̈ړ������Ŏg��)�B
	float			m_atrTime;					//���̎��Ԃ𒴂����瓖����𔭐�������B
	int				m_lv;						//�v���C���[�̃��x���B
	int				m_lvUpEXP;					//���x���A�b�v�ɕK�v�Ȍo���l�B
	int				m_holdEXP;					//�v���C���[�������Ă���o���l�B
	int				m_getEXP;					//�G����擾�����o���l�B
	CSoundSource	m_soundSource;
	CSoundSource	m_soundSource2;
	long long levelUpExpTable[MAX_LEVEL];
	SParicleEmitParameter m_param;
	std::list<CParticleEmitter*>	m_particleEmitterList;
	Light			m_light;
};
