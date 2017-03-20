#include "stdafx.h"
#include "EnemyManager.h"
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
	};
}

//�G�l�~�[�̔z�u���̃e�[�u���B
EnemyManagerLocInfo EnemyChipLocInfoTable[] = {
#include "EnemyPosInfo.h"
};

EnemyManager::EnemyManager()
{
	m_createEnemyFlag = FALSE;
	m_createPos = Vector3Zero;
}

EnemyManager::~EnemyManager()
{
	for (auto enemy : m_enemyskeletonList)
	{
		delete enemy;
	}

	for (auto enemy : m_enemyGoblinList)
	{
		delete enemy;
	}

	delete m_enemyBoss;
}

void EnemyManager::Initialize()
{
	//Unity����o�͂��ꂽ��񂩂�G�𐶐����鏈���B
	for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
		
		//�{�X�̏������B
		if (enemyinfo.modelName == "image\\EnemyBoss.X")
		{
			m_enemyBoss = new EnemyBoss;
			m_enemyBoss->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
		}//���^�̓G�̏������B
		else if (enemyinfo.modelName == "image\\Skeleton@Skin.X")
		{
			EnemySkeleton* newEnemy = new EnemySkeleton;
			newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
			m_enemyskeletonList.push_back(newEnemy);
		}//�S�u�����̏������B
		else if (enemyinfo.modelName == "image\\EnemyGoblin.X")
		{
			EnemyGoblin* newEnemy = new EnemyGoblin;
			newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
			m_enemyGoblinList.push_back(newEnemy);
		}
			
	}
}

void EnemyManager::Update()
{
	//���̍X�V�����B
	{//�G�l�~�[�̐擪���m�ہB
		auto it = m_enemyskeletonList.begin();
		//�G�l�~�[�̃��X�g�̍Ō�܂ŁB
		while (it != m_enemyskeletonList.end())
		{
			//�G�l�~�[��TRUE��Ԃ��ė�����폜�B
			if (TRUE == (*it)->GetDead()) {
				//�G�l�~�[�̉���B
				delete *it;
				//����������̃G�l�~�[���m�ہB
				//erase�֐����Ԃ�l���L���ȃC�e���[�^��Ԃ��Ă����B
				it = m_enemyskeletonList.erase(it);
			}
			else
			{
				//���ɐi�ޏ����B
				it++;
			}
		}
		for (auto enemy : m_enemyskeletonList) {
			enemy->Update();
		}
	}

	//�S�u�����̍X�V�����B
	{
		//�G�l�~�[�̐擪���m�ہB
		auto it = m_enemyGoblinList.begin();
		//�G�l�~�[�̃��X�g�̍Ō�܂ŁB
		while (it != m_enemyGoblinList.end())
		{
			//�G�l�~�[��TRUE��Ԃ��ė�����폜�B
			if (TRUE == (*it)->GetDead()) {
				//�G�l�~�[�̉���B
				delete *it;
				//����������̃G�l�~�[���m�ہB
				//erase�֐����Ԃ�l���L���ȃC�e���[�^��Ԃ��Ă����B
				it = m_enemyGoblinList.erase(it);
			}
			else
			{
				//���ɐi�ޏ����B
				it++;
			}
		}
		for (auto enemy : m_enemyGoblinList) {
			enemy->Update();
		}
	}
	//�{�X�̍X�V�B
	m_enemyBoss->Update();

	if (m_createEnemyFlag == TRUE)
	{
		EnemySkeleton* newEnemy = new EnemySkeleton;
		newEnemy->Initialize("image\\Skeleton@Skin.X", m_createPos, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), Vector3One);
		m_enemyskeletonList.push_back(newEnemy);
		m_createEnemyFlag = FALSE;
	}
}

void EnemyManager::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	//���^�̕`��B
	for (auto enemy: m_enemyskeletonList)
	{
		enemy->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}

	//�S�u�����̕`��B
	for (auto enemy : m_enemyGoblinList)
	{
		enemy->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}
	//�{�X�̕`��B
	m_enemyBoss->Draw(viewMatrix, projMatrix, isShadowReceiver);
	
}

void EnemyManager::SetFrameDeltaTimeMul(float mul)
{
	for (auto enemy : m_enemyskeletonList) {
		enemy->SetFrameDeltaTimeMul(mul);
	}

	for (auto enemy : m_enemyGoblinList) {
		enemy->SetFrameDeltaTimeMul(mul);
	}
	m_enemyBoss->SetFrameDeltaTimeMul(mul);

}