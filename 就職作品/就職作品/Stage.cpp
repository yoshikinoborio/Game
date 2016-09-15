#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_rotation);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Stage::~Stage()
{
	Release();
}

//初期化
void Stage::Initialize()
{
	m_model3d.Initialize("image\\Stage2.X");
}

//更新
void Stage::Update()
{
	D3DXMatrixTranslation(&m_world, m_position.x, m_position.y, m_position.z);
}

// 描画。
void Stage::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight){

	m_model3d.Draw(viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		m_world,
		m_rotation,
		numDiffuseLight
		);
}

//開放。
void Stage::Release()
{
	m_model3d.Release();
}