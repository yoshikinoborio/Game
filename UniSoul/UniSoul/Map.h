#pragma once
#include "SkinModel.h"
#include <string.h>
#include "RigidBody.h"
#include "MeshCollider.h"
#include "Light.h"
#define MapObjectNum 356

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
		bool isShadowReceiver);
private:
	int tableSize;					//位置情報のテーブル数
	SkinModel m_skinModel[MapObjectNum];	//スキンモデル。
	Animation m_animation;		//アニメーション。
	SkinModelData m_skinModelData[MapObjectNum];//スキンモデルデータ。
	MeshCollider	m_meshCollider[MapObjectNum];	//メッシュコライダー。
	RigidBody		m_rigidBody[MapObjectNum];		//剛体。
	Light			m_light;
};