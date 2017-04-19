#pragma once
#include "EnemyBase.h"

class UnityChan;

class EnemyBoss : public EnemyBase
{
public:

	//�R���X�g���N�^�B
	EnemyBoss();

	//�f�X�g���N�^�B
	~EnemyBoss();
	//�������B
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)override;

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowCaster)override;

	//�ǂ����ɔ������Ă��铖���蔻���T���Ă��鏈���B
	void DamageSearch();

	//�_���[�W��Ԃł̏����B
	void DamageProcess();

	//�{�X��J�n�t���O�̎擾�B
	bool GetBossBattleFlag() const
	{
		return m_bossBattleFlag;
	}
private:
	std::unique_ptr<btCollisionObject>	m_collisionObject;		//�R���W�����I�u�W�F�N�g�B
	UnityChan*							m_unitytyan;			//�v���C���[�̃C���X�^���X�B
	D3DXVECTOR3							m_posDifference;		//�v���C���[�Ƃ̋����B
	float								m_atrTime;				//���̎��Ԉȏ�ɂȂ����瓖����𔭐�������B
	bool								m_bossBattleFlag;		//�{�X�킪�n�܂����t���O�B
};