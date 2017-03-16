#pragma once
#include "EnemyBase.h"

//ゴブリンのクラス。
class EnemyGoblin : public EnemyBase
{
public:
	//ゴブリンの状態遷移の種類。
	enum class EnemyGoblinState {
		StateSearch = 0,//索敵中。
		StateWalk,
		StateRun,
		StateAttack,
		StateDamage,
		StateDead,
		StateJump,
		StateFall,
		StateLanding,
	};

	//コンストラクタ。
	EnemyGoblin();

	//デストラクタ。
	~EnemyGoblin();

	//初期化。
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale);

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);

	//死んだかどうかのフラグを取得。
	bool GetDead() const
	{
		return m_isDead;
	}
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	EnemyGoblinState					m_state;				//ゴブリンの状態。
};

