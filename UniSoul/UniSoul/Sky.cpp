#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
	m_scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	//D3DXQUATERNIONÇÃà¯êîÇÕâÒì]é≤(0.0fÅ`1.0fÇ™Max);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_isShadowReceiver = FALSE;
}

Sky::~Sky()
{
	Release();
}

void Sky::Initialize()
{
	m_skinModelData.LoadModelData("image\\Sky.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);
}

void Sky::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void Sky::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
}

void Sky::Release()
{
	m_skinModelData.Release();
}