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
	m_skinModelData.LoadModelData("image\\SkyBox.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//ÉâÉCÉgÇÃê›íËÅB
	//m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	//m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	//m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	//m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	//m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	//m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	//m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	//m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetHasNormalMap(FALSE);
}

void Sky::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void Sky::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix,isShadowReceiver);
}

void Sky::Release()
{
	m_skinModelData.Release();
}