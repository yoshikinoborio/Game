#include "stdafx.h"
#include "Game.h"
#include "Player.h"

Player::Player()
{
	//コンストラクタで初期化する理由は
	//Cplayer pl;
	//pl.Initilize()の実装忘れで初期化されてない変数を無くすため
	D3DXMatrixIdentity(&m_world);
	//D3DXMatrixIdentity(&m_rotation);
	m_scale = D3DXVECTOR3(2.0f,2.0f,2.0f);
	//D3DXQUATERNIONの引数は回転軸(0.0f～1.0fがMax);
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Player::~Player()
{
	Release();
}

//初期化
void Player::Initialize(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//m_model3d.Initialize(pd3dDevice,"image\\unitychan.X");

	m_skinModelData.LoadModelData("image\\Unity.X"/*"image\\Debri.x"*/, &m_animation);
	m_skinModel.Initialize(&m_skinModelData);

	//m_animation.SetAnimationEndtime(AnimationRun, 0.8);
	m_currentAnimSetNo = AnimationInvalid;
	m_animation.PlayAnimation(m_currentAnimSetNo);

	//カメラのインスタンスの取得
	m_camera = game->GetCamera();
}

//更新
void Player::Update()
{
	m_animation.Update(1.0f / 60.0f);

	//パッドによるカメラの奥に移動する処理
	PadMove();

	//パッドのスタートボタンでゲーム終了
	if (g_pad.IsPress(enButtonStart))
	{
		PostQuitMessage(0);
	}
	m_animation.PlayAnimation(AnimationStand, 1.0f);

	m_skinModel.Update(m_position, m_rotation, m_scale);
	//ワールド行列の更新。
	//D3DXMatrixTranslation(&m_world, m_position.x, m_position.y, m_position.z);
}

// 描画。
void Player::Draw(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight){

	/*m_model3d.Draw(pd3dDevice,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		m_world,
		m_rotation,
		numDiffuseLight
		);*/
	m_skinModel.Draw(&viewMatrix, &projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight);
}

//開放。
void Player::Release()
{
	//m_model3d.Release();
	//m_skinModelData.Release();
}

void Player::PadMove()
{
	//カメラの方向にプレイヤーを進める処理
	//左スティックからのカメラ行列における入力を保持
	D3DXVECTOR3 moveDirCameraLocal;
	moveDirCameraLocal.y = 0.0f;
	moveDirCameraLocal.x = g_pad.GetLStickXF();
	moveDirCameraLocal.z = g_pad.GetLStickYF();
	D3DXMATRIX& ViewInv = m_camera->GetViewMatrixInv();//カメラの逆行列を取得
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

	D3DXVECTOR3 moveDir;
	moveDir.x = cameraX.x * moveDirCameraLocal.x + cameraZ.x * moveDirCameraLocal.z;
	moveDir.y = 0.0f;	//Y軸はいらない。
	moveDir.z = cameraX.z * moveDirCameraLocal.x + cameraZ.z * moveDirCameraLocal.z;

	m_position += moveDir;
}