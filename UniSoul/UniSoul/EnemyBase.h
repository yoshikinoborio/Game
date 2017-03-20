#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"

//エネミーの基底クラス。
class EnemyBase : public AnimationModel3D
{
public:
	//ボス以外の状態遷移の種類。
	enum EnemyAnimation {
		enAnimInvalid = -1,
		enAnimWait,		//待機中。
		enAnimWalk,		//歩き中。
		enAnimRun,		//走り中。
		enAnimAttack,	//攻撃中。
		enAnimDamage,	//ダメージ。
		enAnimDead,		//死。
		enAnimJump,		//ジャンプ。
		enAnimFall,		//落下中。
		enAnimLanding,	//着地。
		
	};

	//ボス専用の状態遷移の種類。
	enum BossEnemyAnimation {
		enBossAnimInvalid = -1,
		enBossAnimWait,		//待機中。
		enBossAnimWalk,		//歩き中。
		enBossAnimRun,		//走り中。
		enBossAnimAttack,	//攻撃中。
	};

	//コンストラクタ。
	EnemyBase() {

	}
	//派生クラスのデストラクタを呼ぶためにVirtual。
	virtual~EnemyBase()
	{
	}

	//HPの取得。
	int GetHP() const
	{
		return m_hp;
	}

	//最大HPの取得。
	int GetMaxHP() const
	{
		return m_maxhp;
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

	//ローカル�刄^イムを取得。
	float GetLocalFrameDeltaTime()
	{
		return  m_frameDeltaTime * m_deltaTimeMul;
	}
	//�刄^イムに乗算される値を設定。
	//グローバル�刄^イムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になる。
	void SetFrameDeltaTimeMul(float mul)
	{
		m_deltaTimeMul = mul;
	}
protected:
	D3DXVECTOR3			m_move;								//移動量。
	EnemyAnimation		m_currentAnimSetNo;					//現在再生しているアニメーション。
	BossEnemyAnimation	m_currentBossAnimSetNo;				//ボス専用。
	D3DXVECTOR3			m_moveDir;							//方向。
	int					m_dropEXP;							//倒された時に落とす経験値量。
};