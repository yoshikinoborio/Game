#pragma once
#include "EnemyBase.h"
#include "CharacterController.h"

//ゴブリンの状態遷移の種類。
enum EnemyGoblinState {
	DragonBoarStateSearch = 0,//索敵中。
	DragonBoarStateWalk,
	DragonBoarStateRun,
	DragonBoarStateAttack,
	DragonBoarStateDamage,
	DragonBoarStateDead,
	DragonBoarStateJump,
	DragonBoarStateFall,
	DragonBoarStateLanding,
};

class EnemyGoblin : public EnemyBase
{
public:
	EnemyGoblin();
	~EnemyGoblin();
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale);
	void Update()override;
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	//死んだかどうかのフラグを取得。
	bool GetDead()
	{
		return m_isDead;
	}
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//コリジョンオブジェクト。
	EnemyGoblinState	m_state;
};

