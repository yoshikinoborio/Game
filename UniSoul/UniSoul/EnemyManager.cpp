#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemySkeleton.h"

SkinModelData g_orginSkinModelData;

//�G�l�~�[�^�̉ϒ��z��B
std::vector< EnemySkeleton*> enemyskeletonList;

//�G�l�~�[�̔z�u���B
struct EnemyManagerLocInfo {
	const char* modelName;		//���f���̃p�X�B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�X�P�[���B
};

//�G�l�~�[�̔z�u���̃e�[�u���B
EnemyManagerLocInfo EnemyChipLocInfoTable[] = {
#include "EnemyPosInfo.h"
};

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	Release();
}

void EnemyManager::Initialize()
{
	//�G�̃��f����񂩂�I���W�i�����쐬�B
	g_orginSkinModelData.LoadModelData(EnemyChipLocInfoTable->modelName,&m_animation);

	for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
		EnemySkeleton* newEnemy = new EnemySkeleton;
		newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
		enemyskeletonList.push_back(newEnemy);
	}
}

void EnemyManager::Update()
{
	////�G�l�~�[�̐擪���m�ہB
	//auto it = enemyskeletonList.begin();
	////�G�l�~�[�̃��X�g�̍Ō�܂ŁB
	//while (it != enemyskeletonList.end())
	//{
	//	//�G�l�~�[��false��Ԃ��ė�����폜�B
	//	if ((*it)->GetDead()) {
	//		//�G�l�~�[�̉���B
	//		delete *it;
	//		//����������̃G�l�~�[���m�ہB
	//		it = enemyskeletonList.erase(it);
	//	}
	//	else
	//	{
	//		//���ɐi�ޏ����B
	//		it++;
	//	}
	//}
	for (auto enemy: enemyskeletonList) {
		enemy->Update();
	}
}

void EnemyManager::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	for (auto enemy : enemyskeletonList)
	{
		enemy->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}

	//for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
	//	enemyskeleton->Draw(viewMatrix,projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	//}
}

void EnemyManager::Release()
{
	for (auto enemy : enemyskeletonList)
	{
		enemy->Release();
	}

	//for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
	//	enemyskeleton->Release();
	//}
}