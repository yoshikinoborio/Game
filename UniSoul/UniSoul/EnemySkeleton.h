#pragma once
#include "EnemyBase.h"
#include "CharacterController.h"

class UnityChan;

//�G�l�~�[�̏�ԑJ�ڂ̎�ށB
enum SkeletonState {
	SkeletonStateWait = 0,	//�ҋ@(����)�B
	SkeletonStateWalk,		//�����B
	SkeletonStateRun,		//����B
	SkeletonStateAttack,	//�U���B
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
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	void Release();
private:
	D3DXVECTOR3 m_initPos;						//���̏����ʒu�B
	SkeletonState     m_state;					//���̓G�̏�ԁB
	CharacterController	m_characterController;	//���̓G�̃L�����N�^�R���g���[���B
	float			m_height;					//���̓G�̍����B
	float			m_radius;					//���̓G�̔��a�B
	D3DXVECTOR3     m_move;						//�ړ��ʁB
	UnityChan*		m_unitytyan;				//���j�e�B�����̃C���X�^���X�B
	D3DXVECTOR3		m_unityPos;					//���j�e�B�����̈ʒu�B
};