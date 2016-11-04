#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemySkeleton.h"

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
}

void EnemyManager::Initialize()
{
	for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
		EnemySkeleton* newEnemy = new EnemySkeleton;
		newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
		enemyskeleton.push_back(newEnemy);
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < enemyskeleton.size(); i++) {
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
	for (int i = 0; i < enemyskeleton.size(); i++)
	{
		enemyskeleton[i]->Draw(viewMatrix, projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	}

	//for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
	//	enemyskeleton->Draw(viewMatrix,projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	//}
}

void EnemyManager::Release()
{
	for (int i = 0; i < enemyskeleton.size(); i++)
	{
		enemyskeleton[i]->Release();
	}

	//for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
	//	enemyskeleton->Release();
	//}
}