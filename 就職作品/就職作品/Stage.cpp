#include "stdafx.h"
#include "Game.h"
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

//�������B
void Stage::Initialize()
{
	m_model3d.Initialize("image\\Stage3.X");
	//�e�`�悷��t���O���Z�b�g
	m_model3d.SetShadowReceiverFlag(TRUE);
	
}

//�X�V�B
void Stage::Update()
{
	D3DXMatrixTranslation(&m_world, m_position.x, m_position.y, m_position.z);
}

// �`��B
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

//�J���B
void Stage::Release()
{
	m_model3d.Release();
}