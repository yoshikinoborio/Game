#pragma once
#include "AnimationModel3D.h"

//空クラス
class Sky : public AnimationModel3D
{
public:
	//コンストラクタ。
	Sky();

	//デストラクタ。
	~Sky();

	//初期化。
	void Initialize();

	//更新。
	void Update()override;

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowCaster);
private:
	D3DXVECTOR3		m_position;				//座標。
	D3DXVECTOR3     m_scale;				//スケール。
	D3DXMATRIX		m_world;				//ワールド行列。
	D3DXQUATERNION  m_rotation;				//回転行列。
	bool			m_isShadowReceiver;		//シャドウレシーバー。
};