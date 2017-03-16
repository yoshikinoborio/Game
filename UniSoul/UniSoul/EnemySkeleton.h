#pragma once
#include "EnemyBase.h"

namespace {
	const float SKELETONWAITSPEED = 0.0f;
	const float SKELETONWALKSPEED = 0.02f*60.0f;
	const float SKELETONRUNSPEED = 0.2f*60.0f;
}

class UnityChan;

static D3DXVECTOR3 EnemyCource[] = {
#include "EnemyCource.h"
};

//�X�P���g���N���X�B
class EnemySkeleton : public EnemyBase
{
public:
	//�X�P���g���̏�ԑJ�ڂ̎�ށB
	enum class SkeletonState {
		StateSearch = 0,//���G���B
		StateFind,		//�����B
		StateAttack,	//�U���B
		StateDamage,	//�_���[�W���󂯂Ă���B
		StateDead,		//���B
	};

	//�R���X�g���N�^�B
	EnemySkeleton();

	//�f�X�g���N�^�B
	~EnemySkeleton();

	//�������B
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale);

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);

	//�X�P���g����������Ԃ̎��̉�]�ƈړ��̏����B
	void FindMove();

	//�X�P���g�������G���̎��̉�]�ƈړ��̏����B
	void SearchMove();

	//�_���[�W���󂯂鏈���B
	void Damage();

	//���񂾂��ǂ����̃t���O���擾�B
	bool GetDead() const
	{
		return m_isDead;
	}
private:
	D3DXVECTOR3			m_initPos;					//���̏����ʒu�B
	SkeletonState		m_state;					//���̓G�̏�ԁB
	UnityChan*			m_unitytyan;				//�v���C���[�̃C���X�^���X�B
	D3DXVECTOR3			m_unityPos;					//�v���C���[�̈ʒu�B
	D3DXVECTOR3			m_posDifference;			//�v���C���[�Ƃ̋����B
	D3DXVECTOR3			m_SkeDir;					//�G�̌����x�N�g���B
	float				m_walkTimer;				//�������ԁB
	float				m_atrTime;					//���̎��Ԉȏ�ɂȂ����瓖����𔭐�������B
	int					m_courceArray;				//�R�[�X��`�̐��B
	int					m_mostNearCourceIndex;		//��ԋ߂��R�[�X��`�B
};