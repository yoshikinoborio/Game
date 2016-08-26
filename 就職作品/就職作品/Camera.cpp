#include "stdafx.h"
#include "Game.h"
#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	//初期化
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
}

Camera::~Camera()
{
}

//カメラの初期化
void Camera::Initialize()
{
	m_near = 0.1f;
	m_far = 1000.0f;
	m_aspect = 1.0f;

	m_eyePt = D3DXVECTOR3(0.0f, 7.0f, -5.0f);
	m_lookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//プレイヤーのインスタンスの取得
	m_player = game->GetPlayer();
	
	//注視点から視点に向かうベクトルの算出
	m_toEyeptVector = m_eyePt - m_lookatPt;

}

//カメラの更新
void Camera::Update()
{

	m_rStick_x = g_pad.GetRStickXF();
	m_rStick_y = g_pad.GetRStickYF();

	if (GetAsyncKeyState(VK_UP))
	{
		m_eyePt.y += 1.0f;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_eyePt.y -= 1.0f;
	}

	//右スティックを使った横のカメラ移動
	if (fabsf(m_rStick_x) > 0.0f) {
		//Y軸周りの回転を計算
		D3DXQuaternionRotationAxis(&m_yAxis, &m_upVec,0.1f * m_rStick_x);//Y軸を任意の回転軸にしてクォータニオンを回転
		D3DXMatrixRotationQuaternion(&m_rot, &m_yAxis);//クォータニオンから回転行列を作成
		D3DXVec3Transform(&m_v4, &m_toEyeptVector, &m_rot);//回転行列を使ってm_toEyeptVectorを回転
		m_toEyeptVector.x = m_v4.x;
		m_toEyeptVector.y = m_v4.y;
		m_toEyeptVector.z = m_v4.z;
	}
	//カメラがプレイヤーに追従する処理
	D3DXVECTOR3 V = m_player->GetPlayerPos();
	V.y += 1.0f;
	m_lookatPt = V;	//注視点をプレイヤーの少し上に設定
	m_eyePt = V + m_toEyeptVector;	//カメラをプレイヤーを中心にして移動させる

	//左手座標系ビュー行列を作成する
	D3DXMatrixLookAtLH(&m_viewMatrix,	//左手座標系ビュー行列　D3DXMATRIX構造体へのポインタ
		&m_eyePt,						//視点を定義する D3DXVECTOR3構造体へのポインタ(平行移動で使われる)
		&m_lookatPt,					//カメラの注視対象を定義する D3DXVECTOR3構造体へのポインタ
		&m_upVec						//ワールドの上方、一般には(0,1,0)を定義する D3DXVECTOR3構造体へのポインタ
		);

	//視野に基づいて、左手座標系のパースペクティブ射影行列(3D世界で遠近法を実現する行列)を作成
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix,		//左手座標系のパースペクティブ射影行列を表す D3DXMATRIX 構造体へのポインターを返す
		D3DX_PI / 4,									//y方向の視野角 (画角)
		m_aspect,										//アスペクト比
		m_near,											//近くのビュープレーンのz値(シーンの奥行き方向をどこからどこまで描画するかの設定)
		m_far											//遠くのビュープレーンのz値
		);

}