#include "stdafx.h"
#include "Map.h"

//マップチップの配置情報のテーブル。
MapLocInfo mapChipLocInfoTable[] = {
#include "locationInfo.h"
};

//コンストラクタ。
Map::Map()
{
	
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