#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"

//�G�l�~�[�̊��N���X�B
class EnemyBase : public AnimationModel3D
{
public:
	//�{�X�ȊO�̏�ԑJ�ڂ̎�ށB
	enum EnemyAnimation {
		enAnimInvalid = -1,
		enAnimWait,		//�ҋ@���B
		enAnimWalk,		//�������B
		enAnimRun,		//���蒆�B
		enAnimAttack,	//�U�����B
		enAnimDamage,	//�_���[�W�B
		enAnimDead,		//���B
		enAnimJump,		//�W�����v�B
		enAnimFall,		//�������B
		enAnimLanding,	//���n�B
		
	};

	//�{�X��p�̏�ԑJ�ڂ̎�ށB
	enum BossEnemyAnimation {
		enBossAnimInvalid = -1,
		enBossAnimWait,		//�ҋ@���B
		enBossAnimWalk,		//�������B
		enBossAnimRun,		//���蒆�B
		enBossAnimAttack,	//�U�����B
	};

	//�R���X�g���N�^�B
	EnemyBase() {

	}
	//�h���N���X�̃f�X�g���N�^���ĂԂ��߂�Virtual�B
	virtual~EnemyBase()
	{
	}

	//�����A�j���[�V�������Đ�����Ă��Ă��C�ɂ����ɂł��ŏ����痬���B
	virtual void PlayAnimationForce(const EnemyAnimation& animNo)
	{
		m_animation.PlayAnimation(animNo, 0.3f);
		m_currentAnimSetNo = animNo;
	}

	//�_���[�W���󂯂邱�Ƃ��o���邩����B
	virtual bool IsPossibleApplyDamage(const DamageCollisionWorld::Collision* colli) const
	{
		return true;
	}

	//���[�J�����^�C�����擾�B
	const float& GetLocalFrameDeltaTime() const
	{
		return  m_frameDeltaTime* m_deltaTimeMul;
	}
	//���^�C���ɏ�Z�����l��ݒ�B
	//�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�B
	void SetFrameDeltaTimeMul(const float& mul)
	{
		m_deltaTimeMul = mul;
	}
protected:
	D3DXVECTOR3			m_position;							//���W�B
	D3DXVECTOR3			m_scale;							//�X�P�[���B
	D3DXMATRIX			m_world;							//���[���h�s��B
	CharacterController	m_characterController;				//�L�����N�^�R���g���[���B
	D3DXVECTOR3			m_move;								//�ړ��ʁB
	EnemyAnimation		m_currentAnimSetNo;					//���ݍĐ����Ă���A�j���[�V�����B
	BossEnemyAnimation	m_currentBossAnimSetNo;				//�{�X��p�B
	D3DXQUATERNION		m_rotation;							//��]�s��B
	D3DXVECTOR3			m_moveDir;							//�����B
	float				m_moveSpeed;						//�ړ����x(�������Ƒ��鎞�̑��x�����p)�B
	float				m_currentAngleY;					//���݂̕����B
	float				m_targetAngleY;						//�������������B
	bool				m_isTurn;							//��]�t���O�B
	float				m_height;							//�G�̍����B
	float				m_radius;							//�G�̔��a�B
	float				m_frameDeltaTime = 1.0f / 60.0f;	//1�t���[���̌o�ߎ��ԁB
	float				m_deltaTimeMul = 1.0f;				//���^�C���ɏ�Z�����l�B
	int					m_hp;								//�q�b�g�|�C���g�B
	int					m_dropEXP;							//�|���ꂽ���ɗ��Ƃ��o���l�ʁB
	bool				m_isDead;							//���񂾁B
};