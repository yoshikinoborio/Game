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
	EnemyBoss();
	~EnemyBoss();
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale);
	void Update()override;
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	EnemyBossState	m_state;
};