#include "stdafx.h"
#include "Map.h"
#include "SceneManager.h"

namespace {
	//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
	MapLocInfo mapChipLocInfoTable[] = {
	#include "locationInfo.h"
	};
}

//�R���X�g���N�^�B
Map::Map()
{
	m_createMapFlag = FALSE;
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