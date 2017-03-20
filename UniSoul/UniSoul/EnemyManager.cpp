#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemySkeleton.h"
#include "EnemyGoblin.h"
#include "EnemyBoss.h"

namespace
{
	//エネミーの配置情報。
	struct EnemyManagerLocInfo {
		const char* modelName;		//モデルのパス。
		D3DXVECTOR3	pos;			//座標。
		D3DXQUATERNION	rotation;	//回転。
		D3DXVECTOR3 scale;			//スケール。
	};
}

//エネミーの配置情報のテーブル。
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
	//Unityから出力された情報から敵を生成する処理。
	for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {
		
		//ボスの初期化。
		if (enemyinfo.modelName == "image\\EnemyBoss.X")
		{
			m_enemyBoss = new EnemyBoss;
			m_enemyBoss->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
		}//骨型の敵の初期化。
		else if (enemyinfo.modelName == "image\\Skeleton@Skin.X")
		{
			EnemySkeleton* newEnemy = new EnemySkeleton;
			newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
			m_enemyskeletonList.push_back(newEnemy);
		}//ゴブリンの初期化。
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
	//骨の更新処理。
	{//エネミーの先頭を確保。
		auto it = m_enemyskeletonList.begin();
		//エネミーのリストの最後まで。
		while (it != m_enemyskeletonList.end())
		{
			//エネミーがTRUEを返して来たら削除。
			if (TRUE == (*it)->GetDead()) {
				//エネミーの解放。
				delete *it;
				//解放した次のエネミーを確保。
				//erase関数が返り値が有効なイテレータを返してくれる。
				it = m_enemyskeletonList.erase(it);
			}
			else
			{
				//次に進む処理。
				it++;
			}
		}
		for (auto enemy : m_enemyskeletonList) {
			enemy->Update();
		}
	}

	//ゴブリンの更新処理。
	{
		//エネミーの先頭を確保。
		auto it = m_enemyGoblinList.begin();
		//エネミーのリストの最後まで。
		while (it != m_enemyGoblinList.end())
		{
			//エネミーがTRUEを返して来たら削除。
			if (TRUE == (*it)->GetDead()) {
				//エネミーの解放。
				delete *it;
				//解放した次のエネミーを確保。
				//erase関数が返り値が有効なイテレータを返してくれる。
				it = m_enemyGoblinList.erase(it);
			}
			else
			{
				//次に進む処理。
				it++;
			}
		}
		for (auto enemy : m_enemyGoblinList) {
			enemy->Update();
		}
	}
	//ボスの更新。
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
	//骨型の描画。
	for (auto enemy: m_enemyskeletonList)
	{
		enemy->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}

	//ゴブリンの描画。
	for (auto enemy : m_enemyGoblinList)
	{
		enemy->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}
	//ボスの描画。
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