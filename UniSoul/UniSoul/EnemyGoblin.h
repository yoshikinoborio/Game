#pragma once
#include "EnemyBase.h"

namespace {
	const float GOBLINWAITSPEED = 0.0f;
	const float GOBLINWALKSPEED = 0.005f*60.0f;
	const float GOBLINRUNSPEED = 0.05f*60.0f;
}

class UnityChan;

//�S�u�����̃N���X�B
class EnemyGoblin : public EnemyBase
{
public:
	//�S�u�����̏�ԑJ�ڂ̎�ށB
	enum class EnemyGoblinState {
		StateSearch = 0,//���G���B
		StateFind,		//�����B
		StateAttack,	//�U���B
		StateDamage,	//�_���[�W���󂯂Ă���B
		StateDead,		//���B
		StateJump,		//�W�����v�B
		StateFall,		//�����B
		StateLanding,	//���n�B
	};

	//�R���X�g���N�^�B
	EnemyGoblin();

	//�f�X�g���N�^�B
	~EnemyGoblin();

	//�������B
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)override;

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver)override;

	//�_���[�W�B
	void Damage();
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//�R���W�����I�u�W�F�N�g�B
	EnemyGoblinState					m_state;				//�S�u�����̏�ԁB
	UnityChan*							m_unitytyan;			//�v���C���[�̃C���X�^���X�B
	D3DXVECTOR3							m_posDifference;		//�v���C���[�Ƃ̋����B
	float								m_atrTime;				//���̎��Ԉȏ�ɂȂ����瓖����𔭐�������B
};