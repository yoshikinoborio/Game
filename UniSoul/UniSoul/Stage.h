#pragma once
#include "AnimationModel3D.h"
#include "Light.h"

//ステージクラス
class Stage :public AnimationModel3D
{
public:
	//デストラクタ
	Stage();

	//コンストラクタ
	~Stage();

	//初期化
	void Initialize();

	//更新
	void Update()override;

	//描画
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	D3DXVECTOR3		m_position;			//座標。
	D3DXVECTOR3     m_scale;			//スケール。
	D3DXQUATERNION  m_rotation;			//回転行列。
	Light			m_light;
};