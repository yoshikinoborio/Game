#pragma once
#include "SkinModel.h"
#include <string.h>
#define MapObjectNum 7

//マップチップの配置情報。
struct MapLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//スケール。
};
class Map
{
public:
	Map();
	~Map();
	//初期化。
	void Initialize();
	//更新。
	void Update();
	//描画
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	//解放
	void Release();
private:
	int tableSize;					//位置情報のテーブル数
	SkinModel m_skinModel[MapObjectNum];	//スキンモデル。
	Animation m_animation;		//アニメーション。
	SkinModelData m_skinModelData[MapObjectNum];//スキンモデルデータ。
};

