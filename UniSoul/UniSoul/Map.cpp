#include "stdafx.h"
#include "Map.h"
#include "SceneManager.h"

//マップチップの配置情報のテーブル。
MapLocInfo mapChipLocInfoTable[] = {
#include "locationInfo.h"
};

Map::Map()
{
	//配置情報からマップを構築。
	tableSize = sizeof(mapChipLocInfoTable) / sizeof(mapChipLocInfoTable[0]);
}

Map::~Map()
{
}

void Map::Initialize()
{
	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つをロード。
		m_skinModelData[i].LoadModelData(mapChipLocInfoTable[i].modelName, &m_animation);
		m_skinModel[i].Initialize(&m_skinModelData[i]);

		//ライトの設定。
		m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
		m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
		m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
		m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

		m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));

		m_light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

		m_skinModel[i].SetLight(&m_light);

		m_skinModel[i].SetHasNormalMap(FALSE);


		m_skinModel[i].Update(mapChipLocInfoTable[i].pos, mapChipLocInfoTable[i].rotation, {1.0f, 1.0f, 1.0f});

		//ここから衝突判定絡みの初期化。
		//スキンモデルからメッシュコライダーを作成する。
		D3DXMATRIX* rootBoneMatrix = m_skinModelData[i].GetRootBoneWorldMatrix();
		m_meshCollider[i].CreateFromSkinModel(&m_skinModel[i], rootBoneMatrix);
		//続いて剛体を作成する。
		//まずは剛体を作成するための情報を設定。
		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_meshCollider[i];	//剛体のコリジョンを設定する。
		rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる。
		rbInfo.pos = mapChipLocInfoTable[i].pos;
		rbInfo.rot = mapChipLocInfoTable[i].rotation;
		//剛体を作成。
		m_rigidBody[i].Create(rbInfo);
		//作成した剛体を物理ワールドに追加。
		static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody[i]);
	}
	
}

void Map::Update()
{
	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つを更新。
		m_skinModel[i].Update(mapChipLocInfoTable[i].pos, mapChipLocInfoTable[i].rotation, {1.0f, 1.0f,1.0f });
	}
}

void Map::Draw(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つを描画
		m_skinModel[i].Draw(&viewMatrix, &projMatrix,isShadowReceiver);
	}
}