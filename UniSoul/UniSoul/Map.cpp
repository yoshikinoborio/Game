#include "stdafx.h"
#include "Map.h"
#define  _CRT_SECURE_NO_WARNINGS

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
	Release();
}

void Map::Initialize()
{
	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つをロード。
		m_skinModelData[i].LoadModelData(mapChipLocInfoTable[i].modelName, &m_animation);
		m_skinModel[i].Initialize(&m_skinModelData[i]);
	}
	
}

void Map::Update()
{
	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つを更新。
		m_skinModel[i].Update(mapChipLocInfoTable[i].pos, mapChipLocInfoTable[i].rotation, mapChipLocInfoTable[i].scale);
	}
}

void Map::Draw(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つを描画
		m_skinModel[i].Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	}
}

void Map::Release()
{
	for (int i = 0; i < tableSize; i++)
	{
		//オブジェクト一つ一つを解放
		m_skinModelData[i].Release();
	}
}