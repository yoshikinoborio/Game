#include "stdafx.h"
#include "SceneManager.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemySkeleton.h"
#include "EnemyGoblin.h"
#include "EnemyBoss.h"

namespace
{
	//�G�l�~�[�̔z�u���B
	struct EnemyManagerLocInfo {
		const char* modelName;		//���f���̃p�X�B
		D3DXVECTOR3	pos;			//���W�B
		D3DXQUATERNION	rotation;	//��]�B
		D3DXVECTOR3 scale;			//�X�P�[���B
		short		type;			//�G�̃^�C�v�B
	};

	//�G�l�~�[�̔z�u���̃e�[�u���B
	EnemyManagerLocInfo EnemyChipLocInfoTable[] = {
#include "EnemyPosInfo.h"
	};
}

//�R���X�g���N�^�B
EnemyManager::EnemyManager()
{
	m_createEnemyFlag = FALSE;
	m_createPos = Vector3Zero;
}

//�f�X�g���N�^�B
EnemyManager::~EnemyManager()
{
	//�G�l�~�[�̍폜�B
	for (auto enemy : m_enemyList)
	{
		delete enemy;
	}

	//�{�X���폜����ĂȂ��Ȃ�폜�B
	if (m_enemyBoss != NULL)
	{
		delete	m_enemyBoss;
	}
}

//�������B
void EnemyManager::Initialize()
{

	//Unity����o�͂��ꂽ��񂩂�G�𐶐����鏈���B
	for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {

		//�{�X�̏������B
		if (enemyinfo.type == (short)EnemyType::Boss)
		{
			m_enemyBoss = new EnemyBoss;
			m_enemyBoss->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
		}//�X�P���g���̏������B
		else if (enemyinfo.type == (short)EnemyType::Skeleton)
		{
			EnemyBase* newEnemy = new EnemySkeleton;
			newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
			//�G�l�~�[���X�g�ɒǉ��B
			m_enemyList.push_back(newEnemy);
		}//�S�u�����̏������B
		else if (enemyinfo.type == (short)EnemyType::Goblin)
		{
			EnemyBase* newEnemy = new EnemyGoblin;
			newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
			//�G�l�~�[���X�g�ɒǉ��B
			m_enemyList.push_back(newEnemy);
		}

	}
}

//�X�V�B
void EnemyManager::Update()
{
	//�G�l�~�[���X�g�̍X�V�B
	EnemyListUpdate();

	//�{�X�̍X�V�B
	EnemyBossUpdate();

	//�G�𐶐����鏈���B
	EnemyCreate();
	
}

//�`��B
void EnemyManager::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{

	//�G�l�~�[���X�g�̕`��B
	for (auto enemylist : m_enemyList)
	{
			enemylist->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}

	
	//�{�X���폜����Ă��Ȃ��Ȃ�`��B
	if (m_enemyBoss->GetIsDead() == FALSE)
	{
		//�{�X�̕`��B
		m_enemyBoss->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}	
}

//�G�l�~�[���X�g�̍X�V�B
void EnemyManager::EnemyListUpdate()
{
	//�G�l�~�[�̐擪���m�ہB
	auto it = m_enemyList.begin();
	//�G�l�~�[�̃��X�g�̍Ō�܂ŁB
	while (it != m_enemyList.end())
	{

		//�G�l�~�[��TRUE��Ԃ��ė�����폜�B
		if (TRUE == (*it)->GetIsDead()) {
			//�G�l�~�[�̉���B
			delete *it;
			//����������̃G�l�~�[���m�ہB
			//erase�֐����Ԃ�l���L���ȃC�e���[�^��Ԃ��Ă����B
			it = m_enemyList.erase(it);
		}
		else
		{
			//���ɐi�ޏ����B
			it++;
		}
	}

	//�X�V�����B
	for (auto enemylist : m_enemyList)
	{
		enemylist->Update();
	}
}

//�{�X�̍X�V�B
void EnemyManager::EnemyBossUpdate()
{
	//�����Ă���Ȃ�X�V�B
	if (m_enemyBoss->GetIsDead() == FALSE)
	{
		//�{�X�̍X�V�B
		m_enemyBoss->Update();
	}

}

//���^�C���ɏ�Z�����l��ݒ�B
void EnemyManager::SetFrameDeltaTimeMul(float mul)
{
	for (auto enemy : m_enemyList) {
		enemy->SetFrameDeltaTimeMul(mul);
	}

	
	m_enemyBoss->SetFrameDeltaTimeMul(mul);
}

void EnemyManager::EnemyCreate()
{
	//�G�𐶐�����t���O��TRUE�Ȃ�G���쐬�B
	if (m_createEnemyFlag == TRUE)
	{
		//�t���[�J�������[�h���ɑI������Ă��鐶������I�u�W�F�N�g�̐������擾�B
		int Enemy = g_pScenes->GetCamera()->GetNowObject();
		switch (Enemy)
		{
		case (int)EnemyType::Skeleton:
		{
			//�X�P���g���̐����B
			EnemyBase* newEnemy = new EnemySkeleton;
			newEnemy->Initialize("image\\Skeleton@Skin.X", m_createPos, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), Vector3One);
			//�G�l�~�[���X�g�ɒǉ��B
			m_enemyList.push_back(newEnemy);
			//�������I������̂Ńt���O��FALSE�ɂ���B
			m_createEnemyFlag = FALSE;
			break;
		}
		case (int)EnemyType::Goblin:
		{
			//�S�u���������B
			EnemyBase* newEnemy = new EnemyGoblin;
			newEnemy->Initialize("image\\EnemyGoblin.X", m_createPos, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), Vector3One);
			//�G�l�~�[���X�g�ɒǉ��B
			m_enemyList.push_back(newEnemy);
			//�������I������̂Ńt���O��FALSE�ɂ���B
			m_createEnemyFlag = FALSE;
			break;
		}
		default:
			//�X�P���g���ł��S�u�����ł��Ȃ������̎��͐������Ȃ��̂Ńt���O��FALSE�ɂ���B
			m_createEnemyFlag = FALSE;
			break;
		}

	}
}