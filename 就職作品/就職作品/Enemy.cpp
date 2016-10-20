#include "stdafx.h"
#include "Enemy.h"
#define  _CRT_SECURE_NO_WARNINGS

//�}�b�v�`�b�v�̔z�u���̃e�[�u���B
EnemyLocInfo EnemyChipLocInfoTable[] = {
#include "EnemyPosInfo.h"
};

Enemy::Enemy()
{
	//�z�u��񂩂�}�b�v���\�z�B
	tableSize = sizeof(EnemyChipLocInfoTable) / sizeof(EnemyChipLocInfoTable[0]);
}

Enemy::~Enemy()
{
	Release();
}

void Enemy::Initialize()
{
	for (int i = 0; i < tableSize; i++)
	{
		//�}�b�v�I�u�W�F�N�g�������[�h�B
		m_skinModelData[i].LoadModelData(EnemyChipLocInfoTable[i].modelName, &m_animation);
		m_skinModel[i].Initialize(&m_skinModelData[i]);
	}

}

void Enemy::Update()
{
	for (int i = 0; i < tableSize; i++)
	{

		//�}�b�v�I�u�W�F�N�g�����X�V�B
		m_animation.Update(1.0f / 60.0f);
		m_skinModel[i].Update(EnemyChipLocInfoTable[i].pos, EnemyChipLocInfoTable[i].rotation, EnemyChipLocInfoTable[i].scale);
		
	}
}

void Enemy::Draw(
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
		//�}�b�v�I�u�W�F�N�g����`��
		m_skinModel[i].Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	}
}

void Enemy::Release()
{
	for (int i = 0; i < tableSize; i++)
	{
		//�I�u�W�F�N�g�������
		m_skinModelData[i].Release();
	}
}