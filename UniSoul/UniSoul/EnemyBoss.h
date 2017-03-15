#pragma once
#include "EnemyBase.h"

//�S�u�����̏�ԑJ�ڂ̎�ށB
enum EnemyBossState {
	EnemyBossStateSearch = 0,//���G���B
	EnemyBossStateFind,
	EnemyBossStateAttack,
	EnemyBossStateDamage,
	EnemyBossStateDead,
};

class EnemyBoss : public EnemyBase
{
public:
	//�R���X�g���N�^�B
	EnemyBoss();

	//�f�X�g���N�^�B
	~EnemyBoss();
	//�������B
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale);

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//�R���W�����I�u�W�F�N�g�B
	EnemyBossState						m_state;				//�{�X�G�̏�ԁB
};