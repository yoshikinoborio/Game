#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"
#include "ParticleEmitter.h"
#include "SoundSource.h"

//����namespace���g����static�̎��ɔ������铯���Ƃ̏Փ˂��N���Ȃ��Ȃ�B������������̎g�p�B
namespace {
	const float WALKSPEED = 0.02f*60.0f;	//�����X�s�[�h�B
	const float RUNSPEED = 0.2f*60.0f;		//����X�s�[�h�B
	const float MAX_RUN = 0.6f*60.0f;		//�����܂ł̏���l�B
	const short MAX_LEVEL = 100;			//���x���̍ő�l�B
											//�v���C���[�̔z�u���B
	struct PlayerInfo
	{
		D3DXVECTOR3	pos;			//���W�B
		D3DXQUATERNION	rotation;	//��]�B
	};
};

class CParticleEmitter;
class Camera;


//�v���C���[�̃N���X�B
class UnityChan : public AnimationModel3D
{
public:
	//�R���X�g���N�^�B
	UnityChan();

	//�f�X�g���N�^�B
	~UnityChan();

	//�������B
	void Initialize();

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);

	//�p�b�h�ɂ��J�����̉��Ɉړ����鏈���B
	void PadMove();

	//�ҋ@��Ԃł̏����B
	void WaitProcess();

	//�����Ă����Ԃł̏����B
	void MoveProcess();

	//�W�����v��Ԃł̏����B
	void JumpProcess();

	//�X���C�f�B���O��Ԃł̏����B
	void SLIDProcess();

	//������Ԃł̏����B
	void FallProcess();

	//���n��Ԃł̏����B
	void LandingProcess();

	//�o�b�N�X�e�b�v��Ԃł̏����B
	void BackStepProcess();

	//�_���[�W���󂯂Ă����Ԃł̏����B
	void DamageProcess();

	//�v���C���[�����񂾏�Ԃł̏����B
	void DeadProcess();

	//�U����Ԃł̏����B
	void AttackProcess();

	//�}�b�v�V�t�g��Ԃł̏����B
	void MapShiftProcess();

	//�}�b�v�V�t�g�̏����B
	void MapShift();

	//�W�����v�����B
	void Jump();

	//���x���A�b�v�̏����B
	void LevelUp();

	//�Đ�����A�j���[�V������I�����Đ��B
	void AnimationSelectPlay();

	//�o�b�N�X�e�b�v�B
	void BackStep();

	//�G�̍U���ɓ������Ă��邩�̔���B
	void DamageJudge();

	//�v���C���[��SE�̍X�V�B
	void PlayerSEUpdate();

	//�L�����N�^�[�R���g���[���[�̍X�V�B
	void CharacterControllerUpdate();

	//�G�l�~�[�̓������~�߂�or�ĊJ�����鏈���B
	void EnemyPlayChanger();

	//�v���C���[�̈ʒu�̎擾�B
	const D3DXVECTOR3& GetUnityChanPos () const
	{
		return m_position;
	}

	//�v���C���[�̃��[���h�s��̎擾�B
	const D3DXMATRIX& GetUnityChanWorld() const
	{
		return m_world;
	}

	//�v���C���[�̑傫���̎擾�B
	const D3DXVECTOR3& GetUnityiChanScale() const
	{
		return m_scale;
	}

	//�v���C���[�̉�]�̎擾�B
	const D3DXQUATERNION& GetUnityiChanRotation() const
	{
		return m_rotation;
	}

	//�v���C���[�̈ړ��x�N�g���̎擾�B
	const D3DXVECTOR3& GetUniDir() const
	{
		return m_UniDir;
	}

	//HP�̎擾�B
	int GetHP() const
	{
		return m_hp;
	}

	//�ő�HP�̎擾�B
	int GetMaxHP() const
	{
		return m_maxhp;
	}

	//�o���l�̉��Z�B
	void AddPlayerEXP(int EXP)
	{
		m_getEXP += EXP;
	}

	//�v���C���[�̃��x���̎擾�B
	int GetLv() const
	{
		return m_lv;
	}
	
	//���[�J�����^�C�����擾�B
	float GetLocalFrameDeltaTime() const
	{
		return  m_frameDeltaTime* m_deltaTimeMul;
	}

	//���^�C���ɏ�Z�����l��ݒ�B
	//�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�B
	void SetFrameDeltaTimeMul(float mul)
	{
		m_deltaTimeMul = mul;
	}

	//�v���C���[�ōĐ������A�j���[�V�����̎�ށB
	enum PlayerAnimationNo {
		AnimationWait_00 = 0,	//�ҋ@(����)�B
		AnimationWalk,			//�����B
		AnimationRun,			//����B
		AnimationWait_01,		//�ҋ@(�r�L�΂�)�B
		AnimationWait_02,		//�ҋ@(�N���N��)�B
		AnimationSLID,			//�X���C�f�B���O�B
		AnimationBackStep,		//�o�b�N�X�e�b�v�B
		AnimationFall,			//�������B
		AnimationLanding,		//���n�B
		AnimationJump,			//�W�����v�B
		AnimationPunch,			//�p���`�B
		AnimationRKick,			//�E��i�R��B
		AnimationRotationKick,	//�񂵏R��B
		AnimationSomersault,	//�T�}�[�\���g�B
		AnimationFightingPause,	//�퓬�ł̑ҋ@�B
		AnimationFightingRun,	//�퓬�ł̑���B
		AnimationDaiLanding,	//��������̒��n�B
		AnimationDownFly,		//������сB
		AnimationDamage_00,		//�_���[�W�B
	};

	//�v���C���[�̏�ԑJ�ڂ̎�ށB
	enum PlayerState {
		StateInvalid = -1,
		StateWait,			//�ҋ@�B
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
		StateMapShift		//�}�b�v�V�t�g�B
	};

private:
	D3DXVECTOR3		m_position;							//���W�B
	D3DXVECTOR3     m_scale;							//�X�P�[���B
	D3DXMATRIX		m_world;							//���[���h�s��B
	Camera*         m_camera;							//�J�����̃C���X�^���X�B
	int				m_currentAnimSetNo;					//���ݍĐ����Ă���A�j���[�V�����B
	PlayerState     m_state;							//�v���C���[�̏�ԁB
	D3DXQUATERNION  m_rotation;							//��]�s��B
	D3DXVECTOR3     m_moveDir;							//�J�������狁�߂������B
	D3DXVECTOR3     m_move;								//�ړ��ʁB
	float           m_moveSpeed;						//�ړ����x(�������Ƒ��鎞�̑��x�����p)�B
	float           m_waitAnimetionChangeTime;			//�ҋ@�A�j���[�V�����̐؂�ւ����ԁB
	float			m_currentAngleY;					//���݂̕����B
	float			m_targetAngleY;						//�������������B
	bool			m_isTurn;							//��]�t���O�B
	float           m_saveLStickX;						//���X�e�B�b�N�̍��E�̓��͗ʂ��i�[�B
	float			m_saveLStickY;						//���X�e�B�b�N�̑O��̓��͗ʂ��i�[�B
	CharacterController m_characterController;			//�L�����N�^�R���g���[���B
	float			m_height;							//�v���C���[�̍����B
	float			m_radius;							//�v���C���[�̔��a�B
	bool			m_battleFlag;						//�o�g�������̃t���O�B
	float			m_fallTimer;						//�������ԁB
	int				m_hp;								//�q�b�g�|�C���g�B
	int				m_maxhp;							//�ő�q�b�g�|�C���g�B
	D3DXVECTOR3		m_UniDir;							//�v���C���[�̈ړ��x�N�g��(�G�̈ړ������Ŏg��)�B
	float			m_atrTime;							//���̎��Ԃ𒴂����瓖����𔭐�������B
	int				m_lv;								//�v���C���[�̃��x���B
	int				m_lvUpEXP;							//���x���A�b�v�ɕK�v�Ȍo���l�B
	int				m_holdEXP;							//�v���C���[�������Ă���o���l�B
	int				m_getEXP;							//�G����擾�����o���l�B
	CSoundSource	m_soundSource;						//���n��SE�B
	CSoundSource	m_soundSource2;						//���x���A�b�v��SE�B
	long long		m_levelUpExpTable[MAX_LEVEL];		//���x���A�b�v�ɕK�v�Ȍo���l�e�[�u���B
	CParticleEmitter* m_pEmitter;
	float			m_frameDeltaTime;					//1�t���[���̌o�ߎ��ԁB
	float			m_deltaTimeMul;						//���^�C���ɏ�Z�����l�B
	float			m_time;
};
