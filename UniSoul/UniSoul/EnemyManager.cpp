#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemySkeleton.h"

SkinModelData g_orginSkinModelData;

//エネミー型の可変長配列。
std::vector< EnemySkeleton*> enemyskeletonList;

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
		enemyskeletonList.push_back(newEnemy);
	}
}

void EnemyManager::Update()
{
	////エネミーの先頭を確保。
	//auto it = enemyskeletonList.begin();
	////エネミーのリストの最後まで。
	//while (it != enemyskeletonList.end())
	//{
	//	//エネミーがfalseを返して来たら削除。
	//	if ((*it)->GetDead()) {
	//		//エネミーの解放。
	//		delete *it;
	//		//解放した次のエネミーを確保。
	//		it = enemyskeletonList.erase(it);
	//	}
	//	else
	//	{
	//		//次に進む処理。
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