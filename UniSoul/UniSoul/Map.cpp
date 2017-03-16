#include "stdafx.h"
#include "Map.h"

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
MapLocInfo mapChipLocInfoTable[] = {
#include "locationInfo.h"
};

//�R���X�g���N�^�B
Map::Map()
{
	
}

//�f�X�g���N�^�B
Map::~Map()
{
	for (auto mapList : m_mapChipList)
	{
		delete mapList;
	}
}

//�������B
void Map::Initialize()
{
	for (MapLocInfo& mapinfo : mapChipLocInfoTable) {
		MapChip* newMap = new MapChip;
		newMap->Initialize(mapinfo.modelName, mapinfo.pos, mapinfo.rotation);
		m_mapChipList.push_back(newMap);
	}

}

//�X�V�B
void Map::Update()
{
	
	for (auto mapList : m_mapChipList)
	{
		mapList->Update();
	}
}

//�`��B
void Map::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	
	for (auto mapList : m_mapChipList)
	{
		mapList->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}
}