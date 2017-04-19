#pragma once
#include "EnemyBase.h"

class UnityChan;

//�S�u�����̃N���X�B
class EnemyGoblin : public EnemyBase
{
public:

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
	UnityChan*							m_unitytyan;			//�v���C���[�̃C���X�^���X�B
	D3DXVECTOR3							m_posDifference;		//�v���C���[�Ƃ̋����B
	float								m_atrTime;				//���̎��Ԉȏ�ɂȂ����瓖����𔭐�������B
};