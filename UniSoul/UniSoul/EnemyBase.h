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
		m_animation.PlayAnimation(animNo, 0.3f);
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

	const D3DXVECTOR3& GetPos() const
	{
		return m_position;
	}
protected:
	D3DXVECTOR3			m_move;								//�ړ��ʁB
	EnemyAnimation		m_currentAnimSetNo;					//���ݍĐ����Ă���A�j���[�V�����B
	BossEnemyAnimation	m_currentBossAnimSetNo;				//�{�X��p�B
	D3DXVECTOR3			m_moveDir;							//�����B
	int					m_dropEXP;							//�|���ꂽ���ɗ��Ƃ��o���l�ʁB
};