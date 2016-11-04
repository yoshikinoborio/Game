#include "stdafx.h"
#include "EnemySkeleton.h"

EnemySkeleton::EnemySkeleton()
{
	m_initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = SkeletonStateWait;
	m_height = 0.0f;
	m_radius = 0.0f;
}

EnemySkeleton::~EnemySkeleton()
{
	Release();
}

void EnemySkeleton::Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale)
{
	//敵のモデルのロード。
	m_skinModelData.LoadModelData(modelPath, &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	m_position = pos;
	m_initPos = m_position;
	this->m_rotation = rotation;
	m_scale = scale;
	m_state = SkeletonStateWait;
	m_radius = 0.5f;
	m_height = 1.0f;

	m_characterController.Init(m_radius, m_height, m_position);
}

void EnemySkeleton::Update()
{
	m_animation.Update(1.0f / 60.0f);

	if (m_state==SkeletonStateWait)
	{
		m_currentAnimSetNo = enAnimWait;
	}

	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void EnemySkeleton::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
}

void EnemySkeleton::Release()
{
	m_skinModelData.Release();
}