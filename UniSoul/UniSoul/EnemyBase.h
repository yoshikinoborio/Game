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
	//�h���N���X�̃f�X�g���N�^���ĂԂ��߂�Virtual
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
};