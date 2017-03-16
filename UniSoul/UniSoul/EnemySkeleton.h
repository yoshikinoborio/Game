#pragma once
#include "EnemyBase.h"

namespace {
	const float SKELETONWAITSPEED = 0.0f;
	const float SKELETONWALKSPEED = 0.02f*60.0f;
	const float SKELETONRUNSPEED = 0.2f*60.0f;
}

class UnityChan;

static D3DXVECTOR3 EnemyCource[] = {
#include "EnemyCource.h"
};

//スケルトンクラス。
class EnemySkeleton : public EnemyBase
{
public:
	//スケルトンの状態遷移の種類。
	enum class SkeletonState {
		StateSearch = 0,//索敵中。
		StateFind,		//発見。
		StateAttack,	//攻撃。
		StateDamage,	//ダメージを受けている。
		StateDead,		//死。
	};

	//コンストラクタ。
	EnemySkeleton();

	//デストラクタ。
	~EnemySkeleton();

	//初期化。
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale);

	//更新。
	void Update()override;

	//描画。
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
	bool GetDead() const
	{
		return m_isDead;
	}
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