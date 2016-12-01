#include "stdafx.h"
#include "Enemy.h"

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
		m_skinModelData1[i].LoadModelData(EnemyChipLocInfoTable[i].modelName, &m_animation);
		m_skinModel1[i].Initialize(&m_skinModelData1[i]);

		//ライトの設定。
		m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
		m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
		m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
		m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

		m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
		m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));

		m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
		m_skinModel1[i].SetLight(&m_light);
	}
	m_currentAnimSetNo1 = AnimationInvalid;
	m_state1 = StateWait;

}

void Enemy::Update()
{
	m_animation.Update(1.0f / 60.0f);

	if (m_state1 == StateWait)
	{
		m_currentAnimSetNo1 = AnimationWait;
	}

	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つを更新。
		m_skinModel1[i].Update(EnemyChipLocInfoTable[i].pos, EnemyChipLocInfoTable[i].rotation, EnemyChipLocInfoTable[i].scale);
	}
	m_animation.PlayAnimation(m_currentAnimSetNo1, 0.1f);
}

void Enemy::Draw(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	for (int i = 0; i < tableSize; i++)
	{
		//マップオブジェクト一つ一つを描画
		m_skinModel1[i].Draw(&viewMatrix, &projMatrix,isShadowReceiver);
	}
}

void Enemy::Release()
{
	for (int i = 0; i < tableSize; i++)
	{
		//オブジェクト一つ一つを解放
		m_skinModelData1[i].Release();
	}
}