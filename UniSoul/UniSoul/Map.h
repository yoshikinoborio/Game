#pragma once
#include "MapChip.h"

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
	std::vector<MapChip*> m_mapChipList;	//マップチップのリスト。
};