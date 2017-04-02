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
	//�}�b�v�I�u�W�F�N�g���폜�B
	for (auto mapList : m_mapChipList)
	{
		delete mapList;
	}
}

//�������B
void Map::Initialize()
{
	//�z�u���̃e�[�u�����g���ď������B
	for (MapLocInfo& mapinfo : mapChipLocInfoTable) {
		MapChip* newMap = new MapChip;
		newMap->Initialize(mapinfo.modelName, mapinfo.pos, mapinfo.rotation);
		m_mapChipList.push_back(newMap);
	}

}

//�X�V�B
void Map::Update()
{
	//�}�b�v�I�u�W�F�N�g���X�V�B
	for (auto mapList : m_mapChipList)
	{
		mapList->Update();
	}

	//�}�b�v�I�u�W�F�N�g�𐶐����鏈���B
	CreateMapObject();
}

//�`��B
void Map::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	
	//�}�b�v�I�u�W�F�N�g��`��B
	for (auto mapList : m_mapChipList)
	{
		mapList->Draw(viewMatrix, projMatrix, isShadowReceiver);
	}
}

void Map::CreateMapObject()
{
	//��������t���O��TRUE�Ȃ琶���B
	if (m_createMapFlag == TRUE)
	{
		//�t���[�J�������[�h���ɑI������Ă��鐶������I�u�W�F�N�g�̐������擾�B
		int MapObject = g_pScenes->GetCamera()->GetNowObject();
		switch (MapObject)
		{
		case (int)GameObject::House_A: 
		{
			//�Ƃ̃��f��A�̐����B
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_a2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//�������I������̂Ńt���O��FALSE�ɂ���B
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::House_B:
		{
			//�Ƃ̃��f��B�̐����B
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_b2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//�������I������̂Ńt���O��FALSE�ɂ���B
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::House_C: {
			//�Ƃ̃��f��C�̐����B
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_c2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//�������I������̂Ńt���O��FALSE�ɂ���B
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::House_D:
		{
			//�Ƃ̃��f��D�̐����B
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Building_d2.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//�������I������̂Ńt���O��FALSE�ɂ���B
			m_createMapFlag = FALSE;
			break;
		}
		case (int)GameObject::Yashi:
		{
			//���V�̖؂̃��f���̐����B
			MapChip* newMap = new MapChip;
			newMap->Initialize("image\\Yashi.X", m_createPos, D3DXQUATERNION(-0.71f, 0.00f, 0.00f, 0.71f));
			m_mapChipList.push_back(newMap);
			//�������I������̂Ńt���O��FALSE�ɂ���B
			m_createMapFlag = FALSE;
			break;
		}
		default:
			//��������I�u�W�F�N�g�������ꍇ�̓t���O��FALSE�ɖ߂��B
			m_createMapFlag = FALSE;
			break;
		}

	}
}