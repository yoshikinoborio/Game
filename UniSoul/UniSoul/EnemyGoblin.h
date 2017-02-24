#pragma once
#include "EnemyBase.h"
#include "CharacterController.h"

//�S�u�����̏�ԑJ�ڂ̎�ށB
enum EnemyGoblinState {
	DragonBoarStateSearch = 0,//���G���B
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
	//���񂾂��ǂ����̃t���O���擾�B
	bool GetDead()
	{
		return m_isDead;
	}
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//�R���W�����I�u�W�F�N�g�B
	EnemyGoblinState	m_state;
};

