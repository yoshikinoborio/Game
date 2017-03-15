#pragma once
#include "EnemyBase.h"

#define SKELETONWAITTIME 0.0f
#define SKELETONWALKSPEED 0.02f*60.0f
#define SKELETONRUNSPEED 0.2f*60.0f

class UnityChan;

static D3DXVECTOR3 EnemyCource[] = {
#include "EnemyCource.h"
};


//�X�P���g���̏�ԑJ�ڂ̎�ށB
enum SkeletonState {
	SkeletonStateSearch = 0,//���G���B
	SkeletonStateFind,		//�����B
	SkeletonStateAttack,	//�U���B
	SkeletonStateDamage,	//�_���[�W���󂯂Ă���B
	SkeletonStateDead,		//���B
};

//�X�P���g���N���X�B
class EnemySkeleton : public EnemyBase
{
public:
	EnemySkeleton();
	~EnemySkeleton();
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale);
	void Update()override;
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
	bool GetDead()
	{
		return m_isDead;
	}
	//��]�̏����B
	float Turn(D3DXVECTOR3 dir);
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