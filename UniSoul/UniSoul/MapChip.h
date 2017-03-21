#pragma once
#include "AnimationModel3D.h"
#include <string.h>

namespace {
	//マップチップの配置情報。
	struct MapLocInfo {
		const char* modelName;		//モデル。
		D3DXVECTOR3	pos;			//座標。
		D3DXQUATERNION	rotation;	//回転。
		D3DXVECTOR3 scale;			//スケール。
	};
}

class MapChip :public AnimationModel3D
{
public:
	
	//コンストラクタ。
	MapChip();

	//デストラクタ。
	~MapChip();

	//初期化。
	void Initialize(const char* modelPath, const D3DXVECTOR3& pos, const D3DXQUATERNION& rotation);

	//更新。
	void Update();

	//描画
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
};