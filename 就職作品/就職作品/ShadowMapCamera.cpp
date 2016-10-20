#include "stdafx.h"
#include "Game.h"
#include "ShadowMapCamera.h"

ShadowMapCamera::ShadowMapCamera()
{
	m_shadowmapcameraeyePt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameralookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameraupvec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameranear = 0.0f;
	m_shadowmapcamerafar = 0.0f;
	m_shadowmapcameraaspect = 0.0f;
}

ShadowMapCamera::~ShadowMapCamera()
{

}

//シャドウカメラの初期化。
void ShadowMapCamera::Initialize()
{
	m_shadowmapcameranear = 0.1f;
	m_shadowmapcamerafar = 1000.0f;
	m_shadowmapcameraaspect = 1920.0f / 1020.0f;

	m_shadowmapcameraeyePt = D3DXVECTOR3(0.0f, 50.0f, -2.0f);
	m_shadowmapcameralookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shadowmapcameraupvec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//ユニティちゃんのインスタンスの取得。
	//m_unitychan = game->GetUnityChan();

	//注視点から視点に向かうベクトルの算出。
	//m_toEyeptVector = m_shadowmapcameraeyePt - m_shadowmapcameralookatPt;
}

//シャドウカメラの更新。
void ShadowMapCamera::Update()
{
	//カメラがユニティちゃんに追従する処理。
	//D3DXVECTOR3 V = m_unitychan->GetUnityChanPos();
	//V.y += 1.0f;
	//m_shadowmapcameralookatPt = V;	//注視点をユニティちゃんの少し上に設定。
	//m_shadowmapcameraeyePt = V + m_toEyeptVector;	//カメラをプレイヤーを中心にして移動させる。

	//左手座標系ビュー行列を作成する。
	D3DXMatrixLookAtLH(&m_shadowmapcameraviewMatrix,	
		&m_shadowmapcameraeyePt,						
		&m_shadowmapcameralookatPt,						
		&m_shadowmapcameraupvec							
		);
		
	//視野に基づいて、左手座標系のパースペクティブ射影行列(3D世界で遠近法を実現する行列)を作成。
	D3DXMatrixPerspectiveFovLH(&m_shadowmapcameraprojectionMatrix,		//左手座標系のパースペクティブ射影行列を表す D3DXMATRIX 構造体へのポインターを返す。
		D3DX_PI / 2,													//y方向の視野角 (画角)。
		m_shadowmapcameraaspect,										//アスペクト比。
		m_shadowmapcameranear,											//近くのビュープレーンのz値(シーンの奥行き方向をどこからどこまで描画するかの設定)。
	    m_shadowmapcamerafar											//遠くのビュープレーンのz値。
		);

}