#include "stdafx.h"
#include "Sky.h"
#include "SceneManager.h"

Sky::Sky()
{
	m_scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	//D3DXQUATERNIONの引数は回転軸(0.0f～1.0fがMax);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_isShadowReceiver = FALSE;
}

Sky::~Sky()
{

}

void Sky::Initialize()
{
	m_skinModelData.LoadModelData("image\\SkyBox.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//ライトの設定。
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

	//距離フォグのフラグを設定。
	m_skinModel.SetFogDistFlag(FALSE);
	//高さフォグのフラグを設定。
	m_skinModel.SetFogHeightFlag(TRUE);
	//高さフォグのパラメーターを設定。
	m_skinModel.SetFogHeightParam(100.0f, 10.0f);
}

void Sky::Update()
{
	m_position = g_pScenes->GetUnityChan()->GetUnityChanPos();
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void Sky::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix,isShadowReceiver);
}