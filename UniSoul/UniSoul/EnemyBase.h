#pragma once
#include "AnimationModel3D.h"

//�G�l�~�[�̊��N���X�B
class EnemyBase : public AnimationModel3D
{
public:
	//�G�̃A�j���[�V�����̎�ށB
	enum class EnemyAnimation {
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

	//�G�̏�ԑJ�ڂ̎�ށB
	enum class EnemyState {
		enStateSearch = 0,	//���G���B
		enStateFind,		//�����B
		enStateAttack,		//�U���B
		enStateDamage,		//�_���[�W���󂯂Ă���B
		enStateDead,		//���B
		enStateJump,		//�W�����v�B
		enStateFall,		//�����B
		enStateLanding,		//���n�B
	};

	//�R���X�g���N�^�B
	EnemyBase() {

	}
	//�h���N���X�̃f�X�g���N�^���ĂԂ��߂�Virtual�B
	virtual~EnemyBase()
	{
	}

	//�������B
	virtual void Initialize(const char* modelPath, const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale) {

	}

	//�X�V�B
	virtual void Update() {

	}

	//�`��B
	virtual void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver) {

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

	//TREU�Ȃ玀��ł���AFALSE�Ȃ琶���Ă���B
	bool GetIsDead() const
	{
		return m_isDead;
	}

	//�����A�j���[�V�������Đ�����Ă��Ă��C�ɂ����ɂł��ŏ����痬���B
	virtual void PlayAnimationForce(EnemyAnimation animNo)
	{
		m_animation.PlayAnimation((int)animNo, 0.3f);
		m_currentAnimSetNo = animNo;
	}

	//�_���[�W���󂯂邱�Ƃ��o���邩����B
	virtual bool IsPossibleApplyDamage(const DamageCollisionWorld::Collision* colli) const
	{
		return true;
	}

	//���[�J�����^�C�����擾�B
	float GetLocalFrameDeltaTime()
	{
		return  m_frameDeltaTime * m_deltaTimeMul;
	}
	//���^�C���ɏ�Z�����l��ݒ�B
	//�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�B
	void SetFrameDeltaTimeMul(float mul)
	{
		m_deltaTimeMul = mul;
	}

	//�ʒu�̎擾�B
	const D3DXVECTOR3& GetPos() const
	{
		return m_position;
	}

	//�������͑ҋ@��Ԃł̈ړ��X�s�[�h�B
	//�������͕�����Ԃł̈ړ��X�s�[�h�B
	//��O�����͑����Ԃł̈ړ��X�s�[�h�B
	void SetMoveSpeed(float wait, float walk, float run)
	{
		m_waitSpeed = wait;
		m_walkSpeed = walk;
		m_runSpeed = run;
	}
protected:
	D3DXVECTOR3			m_move;						//�ړ��ʁB
	EnemyAnimation		m_currentAnimSetNo;			//���ݍĐ����Ă���A�j���[�V�����B
	D3DXVECTOR3			m_moveDir;					//�����B
	int					m_dropEXP;					//�|���ꂽ���ɗ��Ƃ��o���l�ʁB
	EnemyState			m_state;					//�G�̏�ԁB
	float				m_waitSpeed;				//�ҋ@��Ԃ̈ړ��X�s�[�h�B
	float				m_walkSpeed;				//������Ԃ̈ړ��X�s�[�h�B
	float				m_runSpeed;					//�����Ԃ̈ړ��X�s�[�h�B
};