#pragma once
#include "Animation.h"
class EnemyBase;
class EnemySkeleton;
class EnemyGoblin;
class EnemyBoss;

//�G�l�~�[�S���̏���������N���X�B
class EnemyManager
{
public:
	enum  class EnemyType
	{
		Skeleton = 0,	//���^�B
		Goblin,			//�S�u�����B
		Boss			//�{�X�B
	};
	//�R���X�g���N�^�B
	EnemyManager();

	//�f�X�g���N�^�B
	~EnemyManager();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();

	//�G�l�~�[���X�g�̍X�V�B
	void EnemyListUpdate();

	//�{�X�̍X�V�B
	void EnemyBossUpdate();

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);

	//�G�𐶐����鏈���B
	void EnemyCreate();
	
	
	const std::vector<EnemyBase*>& GetEnemyList() const
	{
		return m_enemyList;
	}

	//const���ƒ��g��ς��������ɕς���Ȃ��̂ŕς��������p�̂��߂ɂ�����p�ӁB
	std::vector<EnemyBase*>& GetEnemyList()
	{
		return m_enemyList;
	}

	//�{�X�̃C���X�^���X�擾�B
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
	std::vector< EnemyBase*>		m_enemyList;			//�{�X�ȊO�������G�̉ϒ��z��B
	EnemyBoss*						m_enemyBoss;			//�{�X�B
	bool							m_createEnemyFlag;		//�G�𐶐�����t���O�B
	D3DXVECTOR3						m_createPos;			//�G�𐶐����鎞�Ɏg���ʒu�����i�[�B
	
};