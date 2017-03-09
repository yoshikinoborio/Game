#include "stdafx.h"
#include "SceneManager.h"
#include "Camera.h"

Camera::Camera()
{
	m_eyePt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_upVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_near = 0.0f;
	m_far = 0.0f;
	m_aspect = 0.0f;
	m_angle = 0.0f;
	m_toEyeptVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rStick_x = 0.0f;
	m_rStick_y = 0.0f;
	m_cameraFreeFlag = FALSE;
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
	m_lookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//ユニティちゃんのインスタンスの取得。
	m_unitychan = g_pScenes->GetUnityChan();
	
	
	//注視点から視点に向かうベクトルの算出。
	m_toEyeptVector = m_eyePt - m_lookatPt;

}

//カメラの更新。
void Camera::Update()
{
	//右スティックからの入力を取得。
	m_rStick_x = g_pad.GetRStickXF();
	m_rStick_y = g_pad.GetRStickYF();

	// 画面を止めるor再生する処理。
	//ゲームでしか使わないのでキャストゲームシーンクラスにキャスト。
	if (static_cast<GameScene*>(g_pScenes)->GetStopFlag() == FALSE)
	{
		if (g_pad.IsTrigger(enButtonStart))
		{
			static_cast<GameScene*>(g_pScenes)->SetStopFlag(TRUE);
		}
	}
	else
	{
		if (g_pad.IsTrigger(enButtonStart))
		{
			static_cast<GameScene*>(g_pScenes)->SetStopFlag(FALSE);
		}
	}

	//パッドのセレクトボタンでゲーム終了。
	if (g_pad.IsPress(enButtonSelect))
	{
		PostQuitMessage(0);
	}

	//パッドから取得した情報を元にカメラを回転させる処理。
	if (m_cameraFreeFlag==FALSE)
	{
		PadUseRotation();
	}

	//カメラ逆行列の計算(カメラのワールド行列の逆行列)。
	D3DXMatrixInverse(&m_viewMatrixInv, NULL, &m_viewMatrix);

//DEBUG中のみ行う。
#ifdef _DEBUG
	if (g_pad.IsTrigger(enButtonUp))
	{
		m_cameraFreeFlag = TRUE;
	}
	//フリーカメラモードでの処理。
	FreeCameraMode();
#endif // _DEBUG

	if (m_cameraFreeFlag == FALSE) {
		//カメラがユニティちゃんに追従する処理。
		D3DXVECTOR3 V = m_unitychan->GetUnityChanPos();
		V.y += 2.0f;
		m_lookatPt = V;	//注視点をユニティちゃんの少し上に設定。
		m_eyePt = V + m_toEyeptVector;	//カメラをプレイヤーを中心にして移動させる。
	}
		

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

void Camera::PadUseRotation()
{
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
		moveDirCameraLocal.z = g_pad.GetRStickYF();

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
		m_eyePt.y += g_pad.GetLStickYF() *1.0f;
		m_eyePt.z = m_moveDir.z*2.0f;

		m_lookatPt = m_eyePt;
		m_lookatPt.z += 2.0f;

		if (g_pad.IsTrigger(enButtonDown))
		{
			m_cameraFreeFlag = FALSE;
		}
	}
}