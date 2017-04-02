#include "stdafx.h"
#include "SceneManager.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
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
		short		type;			//敵のタイプ。
	};

	//エネミーの配置情報のテーブル。
	EnemyManagerLocInfo EnemyChipLocInfoTable[] = {
#include "EnemyPosInfo.h"
	};
}

//コンストラクタ。
EnemyManager::EnemyManager()
{
	m_createEnemyFlag = FALSE;
	m_createPos = Vector3Zero;
}

//デストラクタ。
EnemyManager::~EnemyManager()
{
	//エネミーの削除。
	for (auto enemy : m_enemyList)
	{
		delete enemy;
	}

	//ボスが削除されてないなら削除。
	if (m_enemyBoss != NULL)
	{
		delete	m_enemyBoss;
	}
}

//初期化。
void EnemyManager::Initialize()
{

	//Unityから出力された情報から敵を生成する処理。
	for (EnemyManagerLocInfo& enemyinfo : EnemyChipLocInfoTable) {

		//ボスの初期化。
		if (enemyinfo.type == (short)EnemyType::Boss)
		{
			m_enemyBoss = new EnemyBoss;
			m_enemyBoss->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
		}//スケルトンの初期化。
		else if (enemyinfo.type == (short)EnemyType::Skeleton)
		{
			EnemyBase* newEnemy = new EnemySkeleton;
			newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
			//エネミーリストに追加。
			m_enemyList.push_back(newEnemy);
		}//ゴブリンの初期化。
		else if (enemyinfo.type == (short)EnemyType::Goblin)
		{
			EnemyBase* newEnemy = new EnemyGoblin;
			newEnemy->Initialize(enemyinfo.modelName, enemyinfo.pos, enemyinfo.rotation, enemyinfo.scale);
			//エネミーリストに追加。
			m_enemyList.push_back(newEnemy);
		}

	}
}

//更新。
void EnemyManager::Update()
{
	//エネミーリストの更新。
	EnemyListUpdate();

	//ボスの更新。
	EnemyBossUpdate();

	//敵を生成する処理。
	EnemyCreate();
	
}

//描画。
void EnemyManager::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{

	//エネミーリストの描画。
	for (auto enemylist : m_enemyList)
	{
			enemylist->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}

	
	//ボスが削除されていないなら描画。
	if (m_enemyBoss->GetIsDead() == FALSE)
	{
		//ボスの描画。
		m_enemyBoss->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}	
}

//エネミーリストの更新。
void EnemyManager::EnemyListUpdate()
{
	//エネミーの先頭を確保。
	auto it = m_enemyList.begin();
	//エネミーのリストの最後まで。
	while (it != m_enemyList.end())
	{

		//エネミーがTRUEを返して来たら削除。
		if (TRUE == (*it)->GetIsDead()) {
			//エネミーの解放。
			delete *it;
			//解放した次のエネミーを確保。
			//erase関数が返り値が有効なイテレータを返してくれる。
			it = m_enemyList.erase(it);
		}
		else
		{
			//次に進む処理。
			it++;
		}
	}

	//更新処理。
	for (auto enemylist : m_enemyList)
	{
		enemylist->Update();
	}
}

//ボスの更新。
void EnemyManager::EnemyBossUpdate()
{
	//生きているなら更新。
	if (m_enemyBoss->GetIsDead() == FALSE)
	{
		//ボスの更新。
		m_enemyBoss->Update();
	}

}

//⊿タイムに乗算される値を設定。
void EnemyManager::SetFrameDeltaTimeMul(float mul)
{
	for (auto enemy : m_enemyList) {
		enemy->SetFrameDeltaTimeMul(mul);
	}

	
	m_enemyBoss->SetFrameDeltaTimeMul(mul);
}

void EnemyManager::EnemyCreate()
{
	//敵を生成するフラグがTRUEなら敵を作成。
	if (m_createEnemyFlag == TRUE)
	{
		//フリーカメラモード時に選択されている生成するオブジェクトの数字を取得。
		int Enemy = g_pScenes->GetCamera()->GetNowObject();
		switch (Enemy)
		{
		case (int)EnemyType::Skeleton:
		{
			//スケルトンの生成。
			EnemyBase* newEnemy = new EnemySkeleton;
			newEnemy->Initialize("image\\Skeleton@Skin.X", m_createPos, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), Vector3One);
			//エネミーリストに追加。
			m_enemyList.push_back(newEnemy);
			//生成し終わったのでフラグをFALSEにする。
			m_createEnemyFlag = FALSE;
			break;
		}
		case (int)EnemyType::Goblin:
		{
			//ゴブリン生成。
			EnemyBase* newEnemy = new EnemyGoblin;
			newEnemy->Initialize("image\\EnemyGoblin.X", m_createPos, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), Vector3One);
			//エネミーリストに追加。
			m_enemyList.push_back(newEnemy);
			//生成し終わったのでフラグをFALSEにする。
			m_createEnemyFlag = FALSE;
			break;
		}
		default:
			//スケルトンでもゴブリンでもない数字の時は生成しないのでフラグをFALSEにする。
			m_createEnemyFlag = FALSE;
			break;
		}

	}
}