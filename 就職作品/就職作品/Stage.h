#pragma once
#include "NonAnimationModel3D.h"

//ステージクラス
class Stage : NonAnimationModel3D
{
public:
	//デストラクタ
	Stage();
	//コンストラクタ
	~Stage();
	//初期化
	void Initialize()override;
	//更新
	void Update()override;
	//描画
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	//解放
	void Release();
private:
	D3DXVECTOR3		m_position;			//座標。
	D3DXMATRIX		m_world;			//ワールド行列。
	D3DXMATRIX		m_rotation;				//回転行列。
};