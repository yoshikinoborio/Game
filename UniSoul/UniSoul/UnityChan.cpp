#include "stdafx.h"
#include "Game.h"
#include "UnityChan.h"

UnityChan::UnityChan()
{
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//D3DXQUATERNIONの引数は回転軸(0.0f～1.0fがMax);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveSpeed = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_height = 0.0f;
	m_radius = 0.0f;
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
	m_animation.SetAnimationEndtime(AnimationBackStep, 1.0f);
	
	//アニメーションのループ設定。
	m_animation.SetAnimationLoopFlag(AnimationSLID,FALSE);
	m_animation.SetAnimationLoopFlag(AnimationBackStep, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_01, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationWait_02, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationLanding, FALSE);
	m_animation.SetAnimationLoopFlag(AnimationJump, FALSE);

	//アニメーション番号の初期化。
	m_currentAnimSetNo = AnimationWait_00;
	
	//ステートの初期化。
	m_state = StateInvalid;

	//回転処理のクラスの初期化。
	m_turn.Initialize();

	//カメラのインスタンスの取得。
	m_camera = game->GetCamera();

	//ユニティちゃんの高さと半径。
	m_height = 1.0f;
	m_radius = 0.5f;

	//キャラクタコントローラを初期化。
	//第一引数が半径、第二引数が高さ、第三引数が位置。
	m_characterController.Initialize(m_radius, m_height, m_position);
	m_characterController.SetGravity(-20.0f);	//重力強め。
}
void UnityChan::Update()
{
	m_animation.Update(1.0f / 60.0f);

	//ユニティちゃんの半径と高さを設定。
	m_characterController.SetRadius(m_radius);
	m_characterController.SetHeight(m_height);

	m_move = m_characterController.GetMoveSpeed();
	
	m_isTurn = FALSE;

	//地面にいる時の処理。
	if (m_characterController.IsOnGround() == TRUE)
	{
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

			//走り状態の時。
			if (m_state == StateRun)
			{
				//入力された値から移動量を求めて一定値を越えたら走りに遷移する。
				if (D3DXVec3LengthSq(&m_move) > 0.6f)
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
			}

			//待機状態の時。
			if (m_state == StateWait_00)
			{
				//待機中にAボタンを押すとバックステップ。
				if (g_pad.IsPress(enButtonA))
				{
					//バックステップの初速度を設定する処理。
					//まずユニティちゃんのワールド行列を取得。
					D3DXMATRIX& UniPos = m_skinModel.GetWorldMatrix();
					//取得してきたワールド行列の前方向の逆方向に速度を設定。
					m_move.x = -UniPos.m[2][0] * 50.0f;
					m_move.z = -UniPos.m[2][2] * 50.0f;
					m_state = StateBackStep;

				}
			}

			//Bボタンを押されたらジャンプ。
			if (g_pad.IsPress(enButtonB))
			{
				//ジャンプ中にジャンプさせないための処理。
				if (!m_characterController.IsJump()) {
					//ジャンプの初速度。
					m_move.y = 10.0f;
					m_characterController.Jump();
					m_state = StateJump;
				}
			}
		}//スライディング。
		else if (m_state == StateSLID)
		{
			//ちょうど体が傾いてるタイミングで半径と高さを変更。
			double AnimTime = m_animation.GetlocalAnimationTime();
			if (AnimTime > 0.5f)
			{
				m_characterController.SetRadius(0.2f);
				m_characterController.SetHeight(0.3f);
			}

			//スライディンが終了したら待機に遷移。
			if (!m_animation.IsPlay())
			{
				m_state = StateWait_00;
			}
		}//バックステップ。
		else if (m_state == StateBackStep)
		{
			//バックステップ後、少しずつ減速。
			m_move *= 0.96f;
			//バックステップの速度を設定。

			//バックステップが終了したら待機に遷移。
			if (!m_animation.IsPlay())
			{
				m_state = StateWait_00;
			}
		}//着地中
		else if (m_state == StateLanding)
		{
			PadMove();

			//着地して動いているか止まっているかをチェック。
			if (D3DXVec3LengthSq(&m_moveDir) > 0.0001f)
			{
				m_state = StateRun;
			}
			else
			{
				//地面に着地して入力をされていなかったら着地に遷移。
				m_state = StateLanding;
			}

			//着地のアニメーションが終わったら待機にする。
			if (!m_animation.IsPlay()) {
				m_state = StateWait_00;
			}

		}//ジャンプ中。
		else if (m_state == StateJump)
		{
			//ジャンプのアニメーションが終わったら落下に遷移。
			if (!m_animation.IsPlay())
			{
				m_state = StateFall;
			}
		}
	}
	else
	{
		//落下中。
		m_state = StateFall;
	}

	//プレイヤーの状態を見て再生するアニメーションを設定。
	{
		//待機(立ち)を設定。
		if (m_state == StateWait_00)
		{
			//待機(立ち)アニメーション。
			m_currentAnimSetNo = AnimationWait_00;
		}
		else if (m_state == StateWait_00)
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
			if (m_state == StateRun)
			{
				//動くスピードを見て走りか歩きかを決める。
				if (D3DXVec3LengthSq(&m_characterController.GetMoveSpeed()) > 32.0f)
				{
					//走りを設定。
					//走りのアニメーション。
					m_currentAnimSetNo = AnimationRun;
				}
				else
				{
					//歩きを設定。
					//歩きのアニメーション。
					m_currentAnimSetNo = AnimationWalk;
				}
			}

			//スライディングを設定。
			if (m_state == StateSLID)
			{
				//スライディングのアニメーション。
				m_currentAnimSetNo = AnimationSLID;
			}

			//落下中を設定。
			if (m_state == StateFall)
			{
				//落下中に地面に着地。
				if (m_characterController.IsOnGround() == TRUE)
				{
					//着地に遷移。
					m_state = StateLanding;
				}
				else
				{
					//落下中のアニメーション。
					m_currentAnimSetNo = AnimationFall;
				}
			}

			//着地中。
			if (m_state == StateLanding)
			{
				//着地中のアニメーション。
				m_currentAnimSetNo = AnimationLanding;
				
			}

			//ジャンプ中。
			if (m_state == StateJump)
			{
				//ジャンプのアニメーション。
				m_currentAnimSetNo = AnimationJump;
			}
		}
	}

	//パッドのスタートボタンでゲーム終了。
	if (g_pad.IsPress(enButtonStart))
	{
		PostQuitMessage(0);
	}

	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_move);
	//キャラクタコントローラーを実行。
	m_characterController.Execute();
	//キャラクターコントロールで計算した位置をプレイヤーの位置に反映。
	m_position = m_characterController.GetPosition();

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

	m_move.x = m_moveDir.x*m_moveSpeed;
	m_move.z = m_moveDir.z*m_moveSpeed;

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