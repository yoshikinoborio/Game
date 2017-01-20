#pragma once
#include "AnimationModel3D.h"

//�G�l�~�[�̊��N���X�B
class EnemyBase : public AnimationModel3D
{
public:
	enum EnemyAnimation {
		enAnimInvalid = -1,
		enAnimWait,		//�ҋ@���B
		enAnimWalk,		//�������B
		enAnimRun,		//���蒆�B
		enAnimAttack,	//�U�����B
		enAnimDamage,	//�_���[�W�B
		enAnimDead,		//���B
	};
	EnemyBase() {

	}
	//�h���N���X�̃f�X�g���N�^���ĂԂ��߂�Virtual�B
	virtual~EnemyBase()
	{
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
	float GetLocalFrameDeltaTime() const
	{
		return  m_frameDeltaTime* m_deltaTimeMul;
	}
	/*!
	* @brief	���^�C���ɏ�Z�����l��ݒ�B
	*@param[in]	mul		�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�B
	*/
	void SetFrameDeltaTimeMul(float mul)
	{
		m_deltaTimeMul = mul;
	}
protected:
	D3DXVECTOR3		m_position;					//���W�B
	D3DXVECTOR3     m_scale;					//�X�P�[���B
	D3DXMATRIX		m_world;					//���[���h�s��B
	EnemyAnimation	m_currentAnimSetNo;			//���ݍĐ����Ă���A�j���[�V�����B
	D3DXQUATERNION  m_rotation;					//��]�s��B
	D3DXVECTOR3     m_moveDir;					//�����B
	float           m_moveSpeed;				//�ړ����x(�������Ƒ��鎞�̑��x�����p)�B
	float			m_currentAngleY;			//���݂̕����B
	float			m_targetAngleY;				//�������������B
	bool			m_isTurn;					//��]�t���O�B
	float			m_height;					//�G�̍����B
	float			m_radius;					//�G�̔��a�B
	float			m_frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB
	float			m_deltaTimeMul = 1.0f;					//���^�C���ɏ�Z�����l�B
};