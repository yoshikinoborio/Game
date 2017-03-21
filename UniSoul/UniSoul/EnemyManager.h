#pragma once
#include "Animation.h"
class EnemySkeleton;
class EnemyGoblin;
class EnemyBoss;

//�G�l�~�[�S���̏���������N���X�B
class EnemyManager
{
public:
	//�R���X�g���N�^�B
	EnemyManager();

	//�f�X�g���N�^�B
	~EnemyManager();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	
	
	const std::vector<EnemySkeleton*>& GetEnemyList() const
	{
		return m_enemyskeletonList;
	}

	//const���ƒ��g��ς��������ɕς���Ȃ��̂ŕς��������p�̂��߂ɂ�����p�ӁB
	std::vector<EnemySkeleton*>& GetEnemyList()
	{
		return m_enemyskeletonList;
	}

	EnemyBoss& GetBoss() 
	{
		return *m_enemyBoss;
	}

	//�G�𐶐�����ʒu�ƃt���O�̐ݒ�B
	void SetEnemyCreate(const D3DXVECTOR3& pos,bool flg)
	{
		m_createPos = pos;
		m_createEnemyFlag = flg;
	}
	//���^�C���ɏ�Z�����l��ݒ�B
	//�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�B
	void SetFrameDeltaTimeMul(float mul);
private:
	std::vector< EnemySkeleton*>	m_enemyskeletonList;	//���^�̓G�̉ϒ��z��B
	std::vector< EnemyGoblin*>		m_enemyGoblinList;		//�S�u�����^�̉ϒ��z��B
	EnemyBoss*						m_enemyBoss;			//�{�X�B
	bool							m_createEnemyFlag;		//�G�𐶐�����t���O�B
	D3DXVECTOR3						m_createPos;			//�G�𐶐����鎞�Ɏg���ʒu�����i�[�B
};