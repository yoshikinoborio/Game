#include "stdafx.h"
#include "Enemy.h"
#define  _CRT_SECURE_NO_WARNINGS

//マップチップの配置情報のテーブル。
EnemyLocInfo EnemyChipLocInfoTable[] = {
#include "EnemyPosInfo.h"
};

Enemy::Enemy()
{
	//配置情報からマップを構築。
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
		//マップオブジェクト一つ一つをロード。
		m_skinModelData[i].LoadModelData(EnemyChipLocInfoTable[i].modelName, &m_animation);
		m_skinModel[i].Initialize(&m_skinModelData[i]);
	}
	m_currentAnimSetNo = AnimationInvalid;
	m_state = StateWait;

}

void Enemy::Update()
{
	m_animation.Update(1.0f / 60.0f);

	if (m_state == StateWait)
	{
		m_currentAnimSetNo = AnimationWait;
	}

	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つを更新。
		m_skinModel[i].Update(EnemyChipLocInfoTable[i].pos, EnemyChipLocInfoTable[i].rotation, EnemyChipLocInfoTable[i].scale);
	}
	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);
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
		//マップオブジェクト一つ一つを描画
		m_skinModel[i].Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
	}
}

void Enemy::Release()
{
	for (int i = 0; i < tableSize; i++)
	{
		//オブジェクト一つ一つを解放
		m_skinModelData[i].Release();
	}
}