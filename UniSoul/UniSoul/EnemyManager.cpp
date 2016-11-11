#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemySkeleton.h"

SkinModelData g_orginSkinModelData;

//�G�l�~�[�^�̉ϒ��z��B
std::vector< EnemySkeleton*> enemyskeleton;

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
		enemyskeleton.push_back(newEnemy);
	}
}

void EnemyManager::Update()
{
	for (unsigned int i = 0; i < enemyskeleton.size(); i++) {
		enemyskeleton[i]->Update();
	}
}

void EnemyManager::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	for (unsigned int i = 0; i < enemyskeleton.size(); i++)
	{
		enemyskeleton[i]->Draw(viewMatrix, projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	}

	//for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
	//	enemyskeleton->Draw(viewMatrix,projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	//}
}

void EnemyManager::Release()
{
	for (unsigned int i = 0; i < enemyskeleton.size(); i++)
	{
		enemyskeleton[i]->Release();
	}

	//for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
	//	enemyskeleton->Release();
	//}
}