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
	//�{�X�̏�ԑJ�ڂ̎�ށB
	enum class EnemyBossState {
		StateSearch = 0,//���G���B
		StateFind,
		StateAttack,
		StateDamage,
		StateDead,
	};

	//�R���X�g���N�^�B
	EnemyBoss();

	//�f�X�g���N�^�B
	~EnemyBoss();
	//�������B
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale);

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//�R���W�����I�u�W�F�N�g�B
	EnemyBossState						m_state;				//�{�X�G�̏�ԁB
	UnityChan*							m_unitytyan;			//�v���C���[�̃C���X�^���X�B
	D3DXVECTOR3							m_posDifference;		//�v���C���[�Ƃ̋����B
	float								m_atrTime;				//���̎��Ԉȏ�ɂȂ����瓖����𔭐�������B
};