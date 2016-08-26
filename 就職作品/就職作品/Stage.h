#pragma once
#include "Model3D.h"

//ステージクラス
class Stage
{
public:
	//デストラクタ
	Stage();
	//コンストラクタ
	~Stage();
	//初期化
	void Initialize(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新
	void Update();
	//描画
	void Draw(LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	//解放
	void Release();
private:
	Model3D					m_model3d;			//3D関係を表示するModel3Dのインスタンスを保持
	D3DXVECTOR3				m_position;			//座標
	D3DXMATRIX				m_world;			//ワールド行列
	D3DXMATRIX				m_rotation;			//回転行列
};