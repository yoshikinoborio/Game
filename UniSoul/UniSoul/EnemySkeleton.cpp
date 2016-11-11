#include "stdafx.h"
#include "EnemySkeleton.h"
#include "Game.h"

EnemySkeleton::EnemySkeleton()
{
	m_initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = SkeletonStateWait;
	m_height = 0.0f;
	m_radius = 0.0f;
	m_unitytyan = game->GetUnityChan();
}

EnemySkeleton::~EnemySkeleton()
{
	Release();
}

void EnemySkeleton::Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation, D3DXVECTOR3 scale)
{
	//オリジナルのモデルからコピー(クローン)を作成。
	m_skinModelData.CloneModelData(g_orginSkinModelData, &m_animation);
	//クローンを使って初期化。
	m_skinModel.Initialize(&m_skinModelData);

	m_position = pos;
	m_initPos = m_position;
	this->m_rotation = rotation;
	m_scale = scale;
	m_state = SkeletonStateWait;
	m_radius = 0.5f;
	m_height = 1.0f;

	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//重力強め。
}

void EnemySkeleton::Update()
{
	m_animation.Update(1.0f / 60.0f);

	m_move = m_characterController.GetMoveSpeed();

	m_unityPos = m_unitytyan->GetUnityChanPos();

	//ユニティちゃんとの距離。
	D3DXVECTOR3 PosDifference;
	PosDifference = m_unityPos - m_position;

	//地面に着いている時。
	if (m_characterController.IsOnGround() == TRUE)
	{
		if (m_state == SkeletonStateWait || m_state == SkeletonStateWait)
		{

		}
	}

	m_characterController.SetMoveSpeed(m_move);

	m_characterController.Execute();

	m_position = m_characterController.GetPosition();

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