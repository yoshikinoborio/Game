#include "stdafx.h"
#include "Game.h"
#include "UnityChan.h"

UnityChan::UnityChan()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//D3DXQUATERNIONの引数は回転軸(0.0f～1.0fがMax);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveSpeed = 0.0f;
	m_isTurn = FALSE;
}

UnityChan::~UnityChan()
{
	Release();
}

void UnityChan::Initialize()
{
	//モデルのロード。
	m_skinModelData.LoadModelData("image\\Unitytyan.X", &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//アニメーションの終了時間の設定。
	m_animation.SetAnimationEndtime(AnimationRun, 0.84f);
	m_animation.SetAnimationEndtime(AnimationSLID, 1.5f);
	m_animation.SetAnimationEndtime(AnimationBackStep, 1.1f);
	
	//アニメーションのループ設定。
	m_animation.SetAnimationLoopFlag(AnimationSLID,FALSE);
	m_animation.SetAnimationLoopFlag(AnimationBackStep, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_01, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_02, FALSE);

	//アニメーション番号の初期化。
	m_currentAnimSetNo = AnimationInvalid;
	
	//ゲーム開始時は待機。
	m_state = StateWait_00;

	//回転処理のクラスの初期化。
	m_turn.Initialize();

	//カメラのインスタンスの取得。
	m_camera = game->GetCamera();
}
void UnityChan::Update()
{
	m_animation.Update(1.0f / 60.0f);

	m_isTurn = FALSE;

	//動いている、止まっている時の処理。
	if (m_state == StateRun || m_state == StateWait_00)
	{

		//パッドによるカメラの奥に移動する処理。
		PadMove();

		//移動量を見て動いているか止まっているかをチェック。
		if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
		{
			m_state = StateRun;
		}
		else
		{
			m_state = StateWait_00;
		}

		//入力された値から移動量を求めて一定値を越えたら走りに遷移する。
		if (D3DXVec3LengthSq(&m_moveDir) > 0.6f)
		{
			//走り状態。
			m_state = StateRun;

			//走る時のスピード。
			m_moveSpeed = RUNSPEED;

			//走っている途中にAボタンが押されるとスライディング。
			if (g_pad.IsPress(enButtonA))
			{
				m_state = StateSLID;
			}
		}
		else
		{
			//歩く時のスピード。
			m_moveSpeed = WALKSPEED;
		}

		//待機状態の時。
		if (m_state == StateWait_00)
		{
			//待機中にAボタンを押すとバックステップ。
			if (g_pad.IsPress(enButtonA))
			{
				m_state = StateBackStep;
				
			}
		}
	}
	else if (m_state == StateSLID)
	{
		m_position += m_moveDir*RUNSPEED;
		//スライディンが終了したら待機に遷移。
		if (!m_animation.IsPlay())
		{
			m_state = StateWait_00;
		}
	}
	else if (m_state == StateBackStep)
	{
		//バックステップが終了したら待機に遷移。
		if (!m_animation.IsPlay())
		{
			m_state = StateWait_00;
		}
	}

	//プレイヤーの状態を見て再生するアニメーションを設定。
	if (m_state == StateWait_00)
	{
		//待機(立ち)を設定。
		m_currentAnimSetNo = AnimationWait_00;
	}
	else if (m_state == StateWait_01)
	{
		m_currentAnimSetNo = AnimationWait_01;
	}
	else if (m_state == StateWait_02)
	{
		m_currentAnimSetNo = AnimationWait_02;
	}
	else if (m_state == StateBackStep)
	{
		m_currentAnimSetNo = AnimationBackStep;
	}
	else
	{
		if (m_moveSpeed == RUNSPEED)
		{
			//走りを設定
			m_currentAnimSetNo = AnimationRun;
		}
		else
		{
			//歩きを設定。
			m_currentAnimSetNo = AnimationWalk;
		}

		if (m_state == StateSLID)
		{
			//スライディングを設定。
			m_currentAnimSetNo = AnimationSLID;
		}
	}

	//パッドのスタートボタンでゲーム終了。
	if (g_pad.IsPress(enButtonStart))
	{
		PostQuitMessage(0);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_position.x += 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_position.x -= 1.0f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_position.z += 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_position.z -= 1.0f;
	}

	m_currentAngleY = m_turn.Update(m_isTurn, m_targetAngleY);

	m_animation.PlayAnimation(m_currentAnimSetNo, 0.1f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void UnityChan::Draw(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isShadowReceiver)
{
	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight, isShadowReceiver);
}

void UnityChan::Release()
{
	m_skinModelData.Release();
}

void UnityChan::PadMove()
{
	//カメラの方向にプレイヤーを進める処理。
	//左スティックからのカメラ行列における入力を保持。
	
	//前後の動き
	if (fabs(g_pad.GetLStickXF()) > 0.0f)
	{
		m_isTurn = true;
	}

	//左右の動き
	if (fabsf(g_pad.GetLStickYF()) > 0.0f)
	{
		m_isTurn = true;
	}

	D3DXVECTOR3 moveDirCameraLocal;
	moveDirCameraLocal.y = 0.0f;
	moveDirCameraLocal.x = g_pad.GetLStickXF();
	moveDirCameraLocal.z = g_pad.GetLStickYF();
	D3DXMATRIX& ViewInv = m_camera->GetViewMatrixInv();//カメラの逆行列を取得。
	//カメラ空間から見た奥方向のベクトルを取得。
	D3DXVECTOR3 cameraZ;
	cameraZ.x = ViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y軸いらない。
	cameraZ.z = ViewInv.m[2][2];
	D3DXVec3Normalize(&cameraZ, &cameraZ);	//Y軸を打ち消しているので正規化する。
	//カメラから見た横方向のベクトルを取得。
	D3DXVECTOR3 cameraX;
	cameraX.x = ViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y軸はいらない。
	cameraX.z = ViewInv.m[0][2];
	D3DXVec3Normalize(&cameraX, &cameraX);	//Y軸を打ち消しているので正規化する。

	m_moveDir.x = cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
	m_moveDir.y = 0.0f;	//Y軸はいらない。
	m_moveDir.z = cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

	m_position += m_moveDir*m_moveSpeed;
	//カメラが向いている方向を正規化。
	D3DXVec3Normalize(&m_moveDir, &m_moveDir);

	if (D3DXVec3Length(&m_moveDir) > 0.0f)
	{
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &m_moveDir));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &forward, &m_moveDir);
		if (axis.x > 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
		//向きたい方向と上方向から軸を作りその軸を回転軸としてクォータニオンを回転。
		D3DXQuaternionRotationAxis(&m_rotation, &axis, m_currentAngleY);
	}
}