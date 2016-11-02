#pragma once
#include "AnimationModel3D.h"
#include <string.h>
#define MapEnemyNum 2

//マップチップの配置情報。
struct EnemyLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//スケール。
};

class Enemy : public AnimationModel3D
{
public:
	Enemy();
	~Enemy();
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
	//エネミーで再生されるアニメーションの種類。
	enum EnemyAnimationNo {
		AnimationInvalid = -1,
		AnimationWait,	//待機(立ち)。
		AnimationWalk,	//歩き。
		AnimationRun,	//走り。
	};

	//エネミーの状態遷移の種類。
	enum EnemyState{
		StateWait = 0,	//待機(立ち)。
		StateWalk,		//歩き。
		StateRun,		//走り。
	};
private:
	int tableSize;					//位置情報のテーブル数
	SkinModel m_skinModel1[MapEnemyNum];	//スキンモデル。
	EnemyAnimationNo m_currentAnimSetNo1;		//アニメーション。
	SkinModelData m_skinModelData1[MapEnemyNum];//スキンモデルデータ。
	EnemyState     m_state1;			//エネミーの状態。
};