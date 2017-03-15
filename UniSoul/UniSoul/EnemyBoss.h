#pragma once
#include "EnemyBase.h"

//ゴブリンの状態遷移の種類。
enum EnemyBossState {
	EnemyBossStateSearch = 0,//索敵中。
	EnemyBossStateFind,
	EnemyBossStateAttack,
	EnemyBossStateDamage,
	EnemyBossStateDead,
};

class EnemyBoss : public EnemyBase
{
public:
	//コンストラクタ。
	EnemyBoss();

	//デストラクタ。
	~EnemyBoss();
	//初期化。
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale);

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	EnemyBossState						m_state;				//ボス敵の状態。
};