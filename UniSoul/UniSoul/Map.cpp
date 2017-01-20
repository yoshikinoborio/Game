#include "stdafx.h"
#include "Map.h"
#include "SceneManager.h"

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
MapLocInfo mapChipLocInfoTable[] = {
#include "locationInfo.h"
};

Map::Map()
{
	//�z�u��񂩂�}�b�v���\�z�B
	tableSize = sizeof(mapChipLocInfoTable) / sizeof(mapChipLocInfoTable[0]);
}

Map::~Map()
{
}

void Map::Initialize()
{
	for (int i = 0; i < tableSize; i++)
	{
		//�}�b�v�I�u�W�F�N�g�������[�h�B
		m_skinModelData[i].LoadModelData(mapChipLocInfoTable[i].modelName, &m_animation);
		m_skinModel[i].Initialize(&m_skinModelData[i]);

		//���C�g�̐ݒ�B
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

		//��������Փ˔��藍�݂̏������B
		//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
		D3DXMATRIX* rootBoneMatrix = m_skinModelData[i].GetRootBoneWorldMatrix();
		m_meshCollider[i].CreateFromSkinModel(&m_skinModel[i], rootBoneMatrix);
		//�����č��̂��쐬����B
		//�܂��͍��̂��쐬���邽�߂̏���ݒ�B
		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_meshCollider[i];	//���̂̃R���W������ݒ肷��B
		rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
		rbInfo.pos = mapChipLocInfoTable[i].pos;
		rbInfo.rot = mapChipLocInfoTable[i].rotation;
		//���̂��쐬�B
		m_rigidBody[i].Create(rbInfo);
		//�쐬�������̂𕨗����[���h�ɒǉ��B
		static_cast<GameScene*>(g_pScenes)->GetPhysicsWorld()->AddRigidBody(&m_rigidBody[i]);
	}
	
}

void Map::Update()
{
	for (int i = 0; i < tableSize; i++)
	{
		//�}�b�v�I�u�W�F�N�g�����X�V�B
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
		//�}�b�v�I�u�W�F�N�g����`��
		m_skinModel[i].Draw(&viewMatrix, &projMatrix,isShadowReceiver);
	}
}