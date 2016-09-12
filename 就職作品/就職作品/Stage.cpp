#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_rotation);
	//m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

Stage::~Stage()
{
	Release();
}

//������
void Stage::Initialize(LPDIRECT3DDEVICE9 pd3dDevice)
{
	m_model3d.Initialize(pd3dDevice,"image\\Stage2.X");
	//m_skinModelData.LoadModelData("image\\Stage2.X",&m_animation);
	//m_skinModel.Initialize(&m_skinModelData);
}

//�X�V
void Stage::Update()
{
	//���[���h�s��̍X�V�B
	//m_skinModel.Update(m_position, m_rotation, m_scale);
	D3DXMatrixTranslation(&m_world, m_position.x, m_position.y, m_position.z);
}

// �`��B
void Stage::Draw(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight){

	m_model3d.Draw(pd3dDevice,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		m_world,
		m_rotation,
		numDiffuseLight
		);
	//m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight);
}

//�J���B
void Stage::Release()
{
	m_model3d.Release();
	//m_skinModelData.Release();
}