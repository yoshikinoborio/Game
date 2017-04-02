#include "stdafx.h"
#include "Map.h"
#include "SceneManager.h"

namespace {
	//マップチップの配置情報のテーブル。
	MapLocInfo mapChipLocInfoTable[] = {
	#include "locationInfo.h"
	};
}

//コンストラクタ。
Map::Map()
{
	m_createMapFlag = FALSE;
}

//デストラクタ。
Map::~Map()
{
	//マップオブジェクトを削除。
	for (auto mapList : m_mapChipList)
	{
		delete mapList;
	}
}

//初期化。
void Map::Initialize()
{
	//配置情報のテーブルを使って初期化。
	for (MapLocInfo& mapinfo : mapChipLocInfoTable) {
		MapChip* newMap = new MapChip;
		newMap->Initialize(mapinfo.modelName, mapinfo.pos, mapinfo.rotation);
		m_mapChipList.push_back(newMap);
	}

}

//更新。
void Map::Update()
{
	//マップオブジェクトを更新。
	for (auto mapList : m_mapChipList)
	{
		mapList->Update();
	}

	//マップオブジェクトを生成する処理。
	CreateMapObject();
}

//描画。
void Map::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	
	//マップオブジェクトを描画。
	for (auto mapList : m_mapChipList)
	{
		mapList->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}
}

void Map::CreateMapObject()
{
	//生成するフラグがTRUEなら生成。
	if (m_createMapFlag == TRUE)
	{
		//フリーカメラモード時に選択されている生成するオブジェクトの数字を取得。
		int MapObject = g_pScenes->GetCamera()->GetNowObject();
		switch (MapObject)
		{
		case (int)GameObject::House_A: 
		{
			//家のモデルAの生成。
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_a2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//生成し終わったのでフラグをFALSEにする。
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::House_B:
		{
			//家のモデルBの生成。
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_b2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//生成し終わったのでフラグをFALSEにする。
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::House_C: {
			//家のモデルCの生成。
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_c2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//生成し終わったのでフラグをFALSEにする。
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::House_D:
		{
			//家のモデルDの生成。
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_d2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//生成し終わったのでフラグをFALSEにする。
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::Yashi:
		{
			//ヤシの木のモデルの生成。
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Yashi.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//生成し終わったのでフラグをFALSEにする。
			m_createMapFlag = FALSE;
			break;
		}
		default:
			//生成するオブジェクトが無い場合はフラグをFALSEに戻す。
			m_createMapFlag = FALSE;
			break;
		}

	}
}