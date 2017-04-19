#pragma once
#include "EnemyBase.h"

class UnityChan;

static D3DXVECTOR3 EnemyCource[] = {
#include "EnemyCource.h"
};

//�X�P���g���N���X�B
class EnemySkeleton : public EnemyBase
{
public:
	//�R���X�g���N�^�B
	EnemySkeleton();

	//�f�X�g���N�^�B
	~EnemySkeleton();

	//�������B
	void Initialize(const char* modelPath,const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)override;

	//�X�V�B
	void Update()override;

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver)override;

	//�X�P���g����������Ԃ̎��̉�]�ƈړ��̏����B
	void FindMove();

	//�X�P���g�������G���̎��̉�]�ƈړ��̏����B
	void SearchMove();

	//�_���[�W���󂯂鏈���B
	void Damage();

	void SetFlag(bool flg)
	{
		m_lightFlag = flg;
	}
private:
	UnityChan*			m_unitytyan;				//�v���C���[�̃C���X�^���X�B
	D3DXVECTOR3			m_unityPos;					//�v���C���[�̈ʒu�B
	D3DXVECTOR3			m_posDifference;			//�v���C���[�Ƃ̋����B
	D3DXVECTOR3			m_SkeDir;					//�G�̌����x�N�g���B
	float				m_walkTimer;				//�������ԁB
	float				m_atrTime;					//���̎��Ԉȏ�ɂȂ����瓖����𔭐�������B
	int					m_courceArray;				//�R�[�X��`�̐��B
	int					m_mostNearCourceIndex;		//��ԋ߂��R�[�X��`�B
	bool				m_lightFlag;				
};