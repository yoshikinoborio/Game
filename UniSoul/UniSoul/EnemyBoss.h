#pragma once
#include "EnemyBase.h"

namespace {
	const float BOSSNWAITSPEED = 0.0f;
	const float BOSSWALKSPEED = 0.02f*60.0f;
	const float BOSSRUNSPEED = 0.2f*60.0f;
}

class UnityChan;

class EnemyBoss : public EnemyBase
{
public:
	//ボスの状態遷移の種類。
	enum class EnemyBossState {
		StateSearch = 0,//索敵中。
		StateFind,
		StateAttack,
		StateDamage,
		StateDead,
	};

	//コンストラクタ。
	EnemyBoss();

	//デストラクタ。
	~EnemyBoss();
	//初期化。
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale);

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	EnemyBossState						m_state;				//ボス敵の状態。
	UnityChan*							m_unitytyan;			//プレイヤーのインスタンス。
	D3DXVECTOR3							m_posDifference;		//プレイヤーとの距離。
	float								m_atrTime;				//この時間以上になったら当たりを発生させる。
};