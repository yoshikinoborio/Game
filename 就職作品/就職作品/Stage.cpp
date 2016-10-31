#include "stdafx.h"
#include "Game.h"
#include "Stage.h"

Stage::Stage()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

Stage::~Stage()
{
	Release();
}

//初期化。
void Stage::Initialize()
{
	m_skinModelData.LoadModelData("image\\Stage3.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);
	//影描画するフラグをセット
	m_skinModel.SetShadowReceiverFlag(TRUE);
	
}

//更新。
void Stage::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

// 描画。
void Stage::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver){

	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
}

//開放。
void Stage::Release()
{
	m_skinModelData.Release();
}