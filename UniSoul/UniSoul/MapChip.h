#pragma once
#include "SkinModel.h"
#include <string.h>
#include "RigidBody.h"
#include "MeshCollider.h"
#include "Light.h"

//マップチップの配置情報。
struct MapLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//スケール。
};

class MapChip
{
public:
	MapChip();
	~MapChip();
	//初期化。
	void Initialize(const char* modelPath, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//更新。
	void Update();
	//描画
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
private:
	SkinModel m_skinModel;			//スキンモデル。
	Animation m_animation;			//アニメーション。
	SkinModelData* m_skinModelData;	//スキンモデルデータ。
	SkinModelDataResources	m_skinModelDataResources;
	MeshCollider	m_meshCollider;	//メッシュコライダー。
	RigidBody		m_rigidBody;	//剛体。
	Light			m_light;

	D3DXVECTOR3		m_position;		//座標。
	D3DXVECTOR3     m_scale;		//スケール。
	D3DXQUATERNION	m_rotation;		//回転。
	bool			m_drawFlag;

};