#pragma once
#include "EnemyBase.h"

#define SKELETONWAITTIME 0.0f
#define SKELETONWALKSPEED 0.02f*60.0f
#define SKELETONRUNSPEED 0.2f*60.0f

class UnityChan;

static D3DXVECTOR3 EnemyCource[] = {
#include "EnemyCource.h"
};


//スケルトンの状態遷移の種類。
enum SkeletonState {
	SkeletonStateSearch = 0,//索敵中。
	SkeletonStateFind,		//発見。
	SkeletonStateAttack,	//攻撃。
	SkeletonStateDamage,	//ダメージを受けている。
	SkeletonStateDead,		//死。
};

//スケルトンクラス。
class EnemySkeleton : public EnemyBase
{
public:
	EnemySkeleton();
	~EnemySkeleton();
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale);
	void Update()override;
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	//スケルトンが発見状態の時の回転と移動の処理。
	void FindMove();
	//スケルトンが索敵中の時の回転と移動の処理。
	void SearchMove();
	//ダメージを受ける処理。
	void Damage();
	//死んだかどうかのフラグを取得。
	bool GetDead()
	{
		return m_isDead;
	}
	//回転の処理。
	float Turn(D3DXVECTOR3 dir);
private:
	D3DXVECTOR3			m_initPos;					//骨の初期位置。
	SkeletonState		m_state;					//骨の敵の状態。
	UnityChan*			m_unitytyan;				//プレイヤーのインスタンス。
	D3DXVECTOR3			m_unityPos;					//プレイヤーの位置。
	D3DXVECTOR3			m_posDifference;			//プレイヤーとの距離。
	D3DXVECTOR3			m_SkeDir;					//敵の向きベクトル。
	float				m_walkTimer;				//歩く時間。
	float				m_atrTime;					//この時間以上になったら当たりを発生させる。
	int					m_courceArray;				//コース定義の数。
	int					m_mostNearCourceIndex;		//一番近いコース定義。
};