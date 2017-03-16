#pragma once
#include "EnemyBase.h"

//�S�u�����̃N���X�B
class EnemyGoblin : public EnemyBase
{
public:
	//�S�u�����̏�ԑJ�ڂ̎�ށB
	enum class EnemyGoblinState {
		StateSearch = 0,//���G���B
		StateWalk,
		StateRun,
		StateAttack,
		StateDamage,
		StateDead,
		StateJump,
		StateFall,
		StateLanding,
	};

	//�R���X�g���N�^�B
	EnemyGoblin();

	//�f�X�g���N�^�B
	~EnemyGoblin();

	//�������B
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale);

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);

	//���񂾂��ǂ����̃t���O���擾�B
	bool GetDead() const
	{
		return m_isDead;
	}
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//�R���W�����I�u�W�F�N�g�B
	EnemyGoblinState					m_state;				//�S�u�����̏�ԁB
};

