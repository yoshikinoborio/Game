#pragma once
#include "EnemyBase.h"
#include "CharacterController.h"
#include "Light.h"

#define SKELETONWAITTIME 0.0f
#define SKELETONWALKSPEED 0.02f*60.0f
#define SKELETONRUNSPEED 0.2f*60.0f

class UnityChan;

//�G�l�~�[�̏�ԑJ�ڂ̎�ށB
enum SkeletonState {
	SkeletonStateSearch = 0,//���G���B
	SkeletonStateFind,		//�����B
	SkeletonStateAttack,	//�U���B
	SkeletonStateDamage,	//�_���[�W���󂯂Ă���B
	SkeletonStateDead,	//���B
};

//�G�l�~�[(�X�P���g��)�N���X�B
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
	void Release();
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
private:
	D3DXVECTOR3 m_initPos;						//���̏����ʒu�B
	SkeletonState     m_state;					//���̓G�̏�ԁB
	CharacterController	m_characterController;	//���̓G�̃L�����N�^�R���g���[���B
	float			m_height;					//���̓G�̍����B
	float			m_radius;					//���̓G�̔��a�B
	D3DXVECTOR3     m_move;						//�ړ��ʁB
	UnityChan*		m_unitytyan;				//���j�e�B�����̃C���X�^���X�B
	D3DXVECTOR3		m_unityPos;					//���j�e�B�����̈ʒu�B
	D3DXVECTOR3		m_posDifference;			//���j�e�B�����Ƃ̋����B
	D3DXVECTOR3		m_SkeDir;					//�G�̌����x�N�g���B
	float			m_walkTimer;				//�������ԁB
	int				m_hp;						//�q�b�g�|�C���g�B
	int				m_dropEXP;					//�|���ꂽ���ɗ��Ƃ��o���l�ʁB
	float			m_atrTime;					//���̎��Ԉȏ�ɂȂ����瓖����𔭐�������B
	bool			m_isDead;					//���񂾁B
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//�R���W�����I�u�W�F�N�g�B
	Light			m_light;
};