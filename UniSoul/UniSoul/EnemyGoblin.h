#pragma once
#include "EnemyBase.h"

namespace {
	const float GOBLINWAITSPEED = 0.0f;
	const float GOBLINWALKSPEED = 0.005f*60.0f;
	const float GOBLINRUNSPEED = 0.05f*60.0f;
}

class UnityChan;

//ゴブリンのクラス。
class EnemyGoblin : public EnemyBase
{
public:
	//ゴブリンの状態遷移の種類。
	enum class EnemyGoblinState {
		StateSearch = 0,//索敵中。
		StateFind,		//発見。
		StateAttack,	//攻撃。
		StateDamage,	//ダメージを受けている。
		StateDead,		//死。
		StateJump,		//ジャンプ。
		StateFall,		//落下。
		StateLanding,	//着地。
	};

	//コンストラクタ。
	EnemyGoblin();

	//デストラクタ。
	~EnemyGoblin();

	//初期化。
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)override;

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver)override;

	//ダメージ。
	void Damage();
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	EnemyGoblinState					m_state;				//ゴブリンの状態。
	UnityChan*							m_unitytyan;			//プレイヤーのインスタンス。
	D3DXVECTOR3							m_posDifference;		//プレイヤーとの距離。
	float								m_atrTime;				//この時間以上になったら当たりを発生させる。
};