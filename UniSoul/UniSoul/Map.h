#pragma once
#include "MapChip.h"

class Map
{
public:
	//コンストラクタ。
	Map();

	//デストラクタ。
	~Map();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//描画
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);

	//マップオブジェクトを生成する位置とフラグの設定。
	void SetMapObjectCreate(const D3DXVECTOR3& pos,bool flg)
	{
		m_createPos = pos;
		m_createMapFlag = flg;
	}
private:
	std::vector<MapChip*> m_mapChipList;	//マップチップのリスト。
	bool				  m_createMapFlag;	//マップ作成フラグ。
	D3DXVECTOR3			  m_createPos;		//敵を生成する時に使う位置情報を格納。
};