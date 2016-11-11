#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemySkeleton.h"

SkinModelData g_orginSkinModelData;

//エネミー型の可変長配列。
std::vector< EnemySkeleton*> enemyskeleton;

//エネミーの配置情報。
struct EnemyManagerLocInfo {
	const char* modelName;		//モデルのパス。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//スケール。
};

//エネミーの配置情報のテーブル。
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
	//敵のモデル情報からオリジナルを作成。
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