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
	for (auto mapList : m_mapChipList)
	{
		delete mapList;
	}
}

//初期化。
void Map::Initialize()
{
	for (MapLocInfo& mapinfo : mapChipLocInfoTable) {
		MapChip* newMap = new MapChip;
		newMap->Initialize(mapinfo.modelName, mapinfo.pos, mapinfo.rotation);
		m_mapChipList.push_back(newMap);
	}

}

//更新。
void Map::Update()
{
	
	for (auto mapList : m_mapChipList)
	{
		mapList->Update();
	}

	if (m_createMapFlag == TRUE)
	{
		int MapObject = g_pScenes->GetCamera()->GetNowObject();
		switch (MapObject)
		{
		case 2: {
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_a2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			m_createMapFlag = FALSE;
			break;
		}
		case 3:
		{
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_b2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			m_createMapFlag = FALSE;
			break;
		}
		case 4: {
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_c2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			m_createMapFlag = FALSE;
			break;
		}
		case 5:
		{
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_d2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			m_createMapFlag = FALSE;
			break;
		}
		case 6:
		{
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Yashi.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			m_createMapFlag = FALSE;
			break;
		}
		default:
			m_createMapFlag = FALSE;
			break;
		}

	}
}

//描画。
void Map::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	
	for (auto mapList : m_mapChipList)
	{
		mapList->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}
}