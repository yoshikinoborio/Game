#pragma once
#include "AnimationModel3D.h"

//エネミーの基底クラス。
class EnemyBase : public AnimationModel3D
{
public:
	//敵のアニメーションの種類。
	enum class EnemyAnimation {
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

	//敵の状態遷移の種類。
	enum class EnemyState {
		enStateSearch = 0,	//索敵中。
		enStateFind,		//発見。
		enStateAttack,		//攻撃。
		enStateDamage,		//ダメージを受けている。
		enStateDead,		//死。
		enStateJump,		//ジャンプ。
		enStateFall,		//落下。
		enStateLanding,		//着地。
	};

	//コンストラクタ。
	EnemyBase() {

	}
	//派生クラスのデストラクタを呼ぶためにVirtual。
	virtual~EnemyBase()
	{
	}

	//初期化。
	virtual void Initialize(const char* modelPath, const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale) {

	}

	//更新。
	virtual void Update() {

	}

	//描画。
	virtual void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver) {

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

	//TREUなら死んでいる、FALSEなら生きている。
	bool GetIsDead() const
	{
		return m_isDead;
	}

	//同じアニメーションが再生されていても気にせずにでも最初から流す。
	virtual void PlayAnimationForce(EnemyAnimation animNo)
	{
		m_animation.PlayAnimation((int)animNo, 0.3f);
		m_currentAnimSetNo = animNo;
	}

	//ダメージを受けることが出来るか判定。
	virtual bool IsPossibleApplyDamage(const DamageCollisionWorld::Collision* colli) const
	{
		return true;
	}

	//ローカル⊿タイムを取得。
	float GetLocalFrameDeltaTime()
	{
		return  m_frameDeltaTime * m_deltaTimeMul;
	}
	//⊿タイムに乗算される値を設定。
	//グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になる。
	void SetFrameDeltaTimeMul(float mul)
	{
		m_deltaTimeMul = mul;
	}

	//位置の取得。
	const D3DXVECTOR3& GetPos() const
	{
		return m_position;
	}

	//第一引数は待機状態での移動スピード。
	//第二引数は歩き状態での移動スピード。
	//第三引数は走り状態での移動スピード。
	void SetMoveSpeed(float wait, float walk, float run)
	{
		m_waitSpeed = wait;
		m_walkSpeed = walk;
		m_runSpeed = run;
	}
protected:
	D3DXVECTOR3			m_move;						//移動量。
	EnemyAnimation		m_currentAnimSetNo;			//現在再生しているアニメーション。
	D3DXVECTOR3			m_moveDir;					//方向。
	int					m_dropEXP;					//倒された時に落とす経験値量。
	EnemyState			m_state;					//敵の状態。
	float				m_waitSpeed;				//待機状態の移動スピード。
	float				m_walkSpeed;				//歩き状態の移動スピード。
	float				m_runSpeed;					//走り状態の移動スピード。
};