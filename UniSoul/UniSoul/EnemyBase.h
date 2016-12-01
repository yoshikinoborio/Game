#pragma once
#include "AnimationModel3D.h"

//エネミーの基底クラス。
class EnemyBase : public AnimationModel3D
{
public:
	enum EnemyAnimation {
		enAnimInvalid = -1,
		enAnimWait,		//待機中。
		enAnimWalk,		//歩き中。
		enAnimRun,		//走り中。
		enAnimAttack,	//攻撃中。
		enAnimDamage,	//ダメージ。
		enAnimDead,		//死。
	};
	EnemyBase() {

	}
	//派生クラスのデストラクタを呼ぶためにVirtual
	virtual~EnemyBase()
	{
	}

	//同じアニメーションが再生されていても気にせずにでも最初から流す。
	virtual void PlayAnimationForce(EnemyAnimation animNo)
	{
		m_animation.PlayAnimation(animNo, 0.3f);
		m_currentAnimSetNo = animNo;
	}

	//ダメージを受けることが出来るか判定。
	virtual bool IsPossibleApplyDamage(const DamageCollisionWorld::Collision* colli) const
	{
		return true;
	}
protected:
	D3DXVECTOR3		m_position;					//座標。
	D3DXVECTOR3     m_scale;					//スケール。
	D3DXMATRIX		m_world;					//ワールド行列。
	EnemyAnimation	m_currentAnimSetNo;			//現在再生しているアニメーション。
	D3DXQUATERNION  m_rotation;					//回転行列。
	D3DXVECTOR3     m_moveDir;					//方向。
	float           m_moveSpeed;				//移動速度(歩く時と走る時の速度調整用)。
	float			m_currentAngleY;			//現在の方向。
	float			m_targetAngleY;				//向きたい方向。
	bool			m_isTurn;					//回転フラグ。
};