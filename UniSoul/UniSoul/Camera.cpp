#include "stdafx.h"
#include "SceneManager.h"
#include "Camera.h"

//次オブジェクトに切り替えができるまで待機する時間。
namespace {
	const short SELECTOBJECT_MOVEWAITTIME = 200;
}

Camera::Camera()
{
	m_eyePt =Vector3Zero;
	m_lookatPt = Vector3Zero;
	m_upVec = Vector3Zero;
	m_near = 0.0f;
	m_far = 0.0f;
	m_aspect = 0.0f;
	m_angle = 0.0f;
	m_toEyeptVector = Vector3Zero;
	m_freeToEyeptVector = Vector3Zero;
	m_rStick_x = 0.0f;
	m_rStick_y = 0.0f;
	m_cameraFreeFlag = FALSE;
	m_nowGameObject = 0;
}

Camera::~Camera()
{

}

//カメラの初期化。
void Camera::Initialize()
{
	m_near = 0.1f;
	m_far = 10000.0f;
	m_aspect = 1920.0f / 1020.0f;

	m_eyePt = D3DXVECTOR3(0.0f, 4.0f, -5.0f);
	m_lookatPt = Vector3Zero;
	m_upVec = Vector3Up;

	//プレイヤーのインスタンスの取得。
	m_unitychan = g_pScenes->GetUnityChan();
	
	
	//注視点から視点に向かうベクトルの算出。
	m_toEyeptVector = m_eyePt - m_lookatPt;

}

//カメラの更新。
void Camera::Update()
{
	// 画面を止めるor再生する処理。
	GameStop();

	//パッドから取得した情報を元にカメラを回転させる処理。
	if (m_cameraFreeFlag == FALSE)
	{
		//パッドを使ったカメラの回転処理。
		PadUseRotation();
		//カメラがプレイヤーに追従する処理。
		TargetPlayer();
	}

//DEBUG中のみ行う。
#ifdef _DEBUG
	FreeCameraFlagChanger();
	//フリーカメラモードでの処理。
	FreeCameraMode();
#endif // _DEBUG
	
	//カメラのビュー行列とパースペクティブ射影行列の作成。
	CameraMatrixUpadate();

	//カメラ逆行列の計算(カメラのワールド行列の逆行列)。
	D3DXMatrixInverse(&m_viewMatrixInv, NULL, &m_viewMatrix);
	
	//ゲームの終了。
	GameEnd();
}

void Camera::PadUseRotation()
{
	//右スティックからの入力を取得。
	m_rStick_x = g_pad.GetRStickXF();
	m_rStick_y = g_pad.GetRStickYF();

	//右スティックを使った縦のカメラ移動。
	if (fabsf(m_rStick_y) > 0.0f) {
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &m_upVec, &m_toEyeptVector);//上方向と横方向に直行するベクトルを求める。
		D3DXQuaternionRotationAxis(&m_zAxis, &Cross, 0.03f*m_rStick_y);//上で求めたベクトルを回転軸にしてクォータニオンを回転。
		D3DXMatrixRotationQuaternion(&m_rot, &m_zAxis);//クォータニオンから回転行列を作成。
		D3DXVec3Transform(&m_v4, &m_toEyeptVector, &m_rot);//回転行列を使ってm_toEyeptVectorを回転。
		D3DXVECTOR3 m_toEyeptVectorOld = m_toEyeptVector;
		m_toEyeptVector.x = m_v4.x;
		m_toEyeptVector.y = m_v4.y;
		m_toEyeptVector.z = m_v4.z;
		D3DXVECTOR3 toPosDir;
		D3DXVec3Normalize(&toPosDir, &m_toEyeptVector);
		if (toPosDir.y < -0.5f) {
			//カメラが上向きすぎ。
			m_toEyeptVector = m_toEyeptVectorOld;
		}
		else if (toPosDir.y > 0.8f) {
			//カメラが下向きすぎ。
			m_toEyeptVector = m_toEyeptVectorOld;
		}
	}

	//右スティックを使った横のカメラ移動。
	if (fabsf(m_rStick_x) > 0.0f) {
		//Y軸周りの回転を計算。
		D3DXQuaternionRotationAxis(&m_yAxis, &m_upVec, 0.03f * m_rStick_x);//Y軸を任意の回転軸にしてクォータニオンを回転。
		D3DXMatrixRotationQuaternion(&m_rot, &m_yAxis);//クォータニオンから回転行列を作成。
		D3DXVec3Transform(&m_v4, &m_toEyeptVector, &m_rot);//回転行列を使ってm_toEyeptVectorを回転。
		m_toEyeptVector.x = m_v4.x;
		m_toEyeptVector.y = m_v4.y;
		m_toEyeptVector.z = m_v4.z;
	}
}

void Camera::FreeCameraMode()
{
	if (m_cameraFreeFlag == TRUE) {
		D3DXVECTOR3 moveDirCameraLocal;
		moveDirCameraLocal.y = 0.0f;
		moveDirCameraLocal.x = g_pad.GetLStickXF();
		moveDirCameraLocal.z = g_pad.GetLStickYF();

		D3DXMATRIX& ViewInv = m_viewMatrixInv;//カメラの逆行列を取得。
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

		m_moveDir.x += cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
		m_moveDir.y = 0.0f;	//Y軸はいらない。
		m_moveDir.z += cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

		m_eyePt.x = m_moveDir.x*2.0f;
		m_eyePt.y += g_pad.GetRStickYF() *1.0f;
		m_eyePt.z = m_moveDir.z*2.0f;

		m_lookatPt = m_eyePt;
		m_lookatPt.z += 2.0f;

		//右スティックからの入力を取得。
		m_rStick_x = g_pad.GetRStickXF();
		//右スティックを使った横のカメラ移動。
		if (fabsf(m_rStick_x) > 0.0f) {
			//Y軸周りの回転を計算。
			D3DXQuaternionRotationAxis(&m_yAxis, &m_upVec, 0.03f * m_rStick_x);//Y軸を任意の回転軸にしてクォータニオンを回転。
			D3DXMatrixRotationQuaternion(&m_rot, &m_yAxis);//クォータニオンから回転行列を作成。
			D3DXVec3Transform(&m_v4, &m_freeToEyeptVector, &m_rot);//回転行列を使ってm_toEyeptVectorを回転。
			m_freeToEyeptVector.x = m_v4.x;
			m_freeToEyeptVector.y = m_v4.y;
			m_freeToEyeptVector.z = m_v4.z;
		}



		m_eyePt = m_lookatPt + m_freeToEyeptVector;	//カメラをプレイヤーを中心にして移動させる。

		//現在の時間の取得。
		m_nowTime = timeGetTime();

		//一定時間超えないとオブジェクトの切り替えは発生しない。
		if (m_nowTime - m_selectMoveTime > SELECTOBJECT_MOVEWAITTIME) {
			m_selectMoveTime = m_nowTime;

			//十字キー左が押されたら。
			if (g_pad.IsPress(enButtonLeft))
			{
				//選択しているオブジェクトをずらす。
				m_nowGameObject -= 1;

				//ずらした結果選択出来るオブジェクトの先頭までまで到達したら最後尾に戻す。
				if (m_nowGameObject < (int)GameObject::Skeleton)
				{
					m_nowGameObject = (int)GameObject::ObjectNum - 1;
				}
			}
			else
			{
				//何も押されていない間は0にする。
				m_selectMoveTime = 0;
			}
		}

		//一定時間超えないとオブジェクトの切り替えは発生しない。
		if (m_nowTime - m_selectMoveTime > SELECTOBJECT_MOVEWAITTIME) {
			m_selectMoveTime = m_nowTime;

			//十字キー右が押されたら。
			if (g_pad.IsPress(enButtonRight))
			{
				//選択しているオブジェクトをずらす。
				m_nowGameObject += 1;

				//ずらした結果選択出来るオブジェクトの最後尾にまで到達したら先頭に戻す。
				if (m_nowGameObject >= (int)GameObject::ObjectNum)
				{
					m_nowGameObject = (int)GameObject::Skeleton;
				}
			}
			else
			{
				//何も押されていない間は0にする。
				m_selectMoveTime = 0;
			}
		}

		//Aボタンを押すと敵を生成。
		if (g_pad.IsTrigger(enButtonRB1))
		{
			//敵を生成するフラグの切り替え。
			g_enemyManager->SetEnemyCreate(m_lookatPt, TRUE);

			//マップオブジェクトを生成するフラグの切り替え。
			static_cast<GameScene*>(g_pScenes)->GetMap()->SetMapObjectCreate(m_lookatPt, TRUE);

			if (m_nowGameObject == (int)GameObject::Player)
			{
				m_unitychan->SetPos(m_eyePt);
			}
		}

		//フリーカメラフラグの操作。
		FreeCameraFlagChanger();
	}
}

void Camera::GameStop()
{
	//ゲームでしか使わないのでキャストゲームシーンクラスにキャスト。
	if (static_cast<GameScene*>(g_pScenes)->GetStopFlag() == FALSE)
	{
		//ゲームの停止。
		if (g_pad.IsTrigger(enButtonStart))
		{
			static_cast<GameScene*>(g_pScenes)->SetStopFlag(TRUE);
		}
	}
	else
	{
		//ゲームの再生。
		if (g_pad.IsTrigger(enButtonStart))
		{
			static_cast<GameScene*>(g_pScenes)->SetStopFlag(FALSE);
		}
	}
}

void Camera::CameraMatrixUpadate()
{
	//左手座標系ビュー行列を作成する。
	D3DXMatrixLookAtLH(&m_viewMatrix,	//左手座標系ビュー行列　D3DXMATRIX構造体へのポインタ。
		&m_eyePt,						//視点を定義する D3DXVECTOR3構造体へのポインタ(平行移動で使われる)。
		&m_lookatPt,					//カメラの注視対象を定義する D3DXVECTOR3構造体へのポインタ。
		&m_upVec						//ワールドの上方、一般には(0,1,0)を定義する D3DXVECTOR3構造体へのポインタ。
	);

	//視野に基づいて、左手座標系のパースペクティブ射影行列(3D世界で遠近法を実現する行列)を作成。
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix,		//左手座標系のパースペクティブ射影行列を表す D3DXMATRIX 構造体へのポインターを返す。
		D3DX_PI / 4,									//y方向の視野角 (画角)。
		m_aspect,										//アスペクト比。
		m_near,											//近くのビュープレーンのz値(シーンの奥行き方向をどこからどこまで描画するかの設定)。
		m_far											//遠くのビュープレーンのz値。
	);
}

void Camera::TargetPlayer()
{
	D3DXVECTOR3 V = m_unitychan->GetUnityChanPos();
	V.y += 2.0f;
	m_lookatPt = V;	//注視点をプレイヤーの少し上に設定。
	m_eyePt = V + m_toEyeptVector;	//カメラをプレイヤーを中心にして移動させる。
}

void Camera::GameEnd()
{
	//パッドのセレクトボタンでゲーム終了。
	if (g_pad.IsPress(enButtonSelect))
	{
		PostQuitMessage(0);
	}
}

void Camera::FreeCameraFlagChanger()
{
	if (g_pad.IsTrigger(enButtonUp))
	{
		D3DXVECTOR3 FreeEyePt = D3DXVECTOR3(0.0f, 2.04f, 0.0f);
		D3DXVECTOR3 FreeLookatPt = D3DXVECTOR3(0.0f, 2.04f, 2.0f);
		m_freeToEyeptVector = FreeEyePt - FreeLookatPt;
		m_cameraFreeFlag = TRUE;
	}

	if (g_pad.IsTrigger(enButtonDown))
	{
		m_cameraFreeFlag = FALSE;
	}
}