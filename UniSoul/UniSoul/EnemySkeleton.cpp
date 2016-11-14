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
	m_posDifference = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = SkeletonStateSearch;
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

	m_isTurn = FALSE;

	m_posDifference = m_unityPos - m_position;
	
	//地面に着いている時。
	if (m_characterController.IsOnGround() == TRUE)
	{
		if (m_state == SkeletonStateSearch)
		{
			//ユニティちゃんが近くに来た時の処理。
			if (D3DXVec3LengthSq(&m_posDifference) < 200.0f)
			{
				m_state = SkeletonStateFind;
				m_moveSpeed = SKELETONRUNSPEED;
			}
			else
			{
				//近くにいない時は索敵中。
				m_state == SkeletonStateSearch;
				m_moveSpeed = SKELETONWALKSPEED;
			}
			10
		}//索敵範囲内にユニティちゃんを発見。
		else if (m_state == SkeletonStateFind)
		{
			//発見中に近くに行くと攻撃する。
			if (D3DXVec3LengthSq(&m_posDifference) < 10.0f)
			{
				m_state = SkeletonStateAttack;
			}
		}
		//回転と移動の処理。
		SkeletonMove();

	}

	if (m_state==SkeletonStateSearch)
	{
		m_currentAnimSetNo = enAnimWait;
	}
	else if (m_state == SkeletonStateFind)
	{
		m_currentAnimSetNo = enAnimRun;
	}

	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_move);
	//キャラクタコントローラーを実行。
	m_characterController.Execute();
	//キャラクターコントロールで計算した位置をエネミーの位置に反映。
	m_position = m_characterController.GetPosition();

	//向きたい方向と上方向から軸を作りその軸を回転軸としてクォータニオンを回転。
	D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), m_targetAngleY);

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

void EnemySkeleton::SkeletonMove()
{
	m_isTurn = TRUE;

	m_posDifference.y = 0.0f;

	//キャラが向いている方向を正規化。
	D3DXVec3Normalize(&m_posDifference, &m_posDifference);
	//敵をユニティちゃんの向きに進ませる。
	m_move = m_moveSpeed*m_posDifference;

	//回転の処理。
	if (D3DXVec3Length(&m_posDifference) > 0.0f)
	{
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//回転量の計算。
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &m_posDifference));
		D3DXVECTOR3 axis;
		//ベクトルとベクトルの外積を取って+,-どちらに回すかを決める。
		D3DXVec3Cross(&axis, &forward, &m_posDifference);
		D3DXVec3Normalize(&axis, &axis);
		//負数の時は+にする。
		if (axis.y < 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
	}
}